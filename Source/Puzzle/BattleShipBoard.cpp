// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleShipBoard.h"
#include "Block.h"
#include "EngineMinimal.h"

// Sets default values
ABattleShipBoard::ABattleShipBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot.Get();

	// Default values
	Size = 10;
	BlockSpacing = 115.0f;
	SizeOfBlock = FVector(0.3f, 0.3f, 0.1f);
}

// Called when the game starts or when spawned
void ABattleShipBoard::BeginPlay()
{
	Super::BeginPlay();
	
	// Loop to spawn each of the blocks that composes the board
	for (int32 Y_Index = 0; Y_Index < Size; Y_Index++)
	{
		for (int32 X_Index = 0; X_Index < Size; X_Index++)
		{
			// Obtain the index of the block
			int32 Index = CalculateIndex(X_Index, Y_Index);

			// Make position vector
			const FVector location = CalculateLocation(Index) + GetActorLocation();

			// Spawn block
			TWeakObjectPtr<ABlock> NewBlock = GetWorld()->SpawnActor<ABlock>(location, FRotator(0.0f, 0.0f, 0.0f));

			// Modify its scale
			NewBlock->GetBlockMesh()->SetRelativeScale3D(SizeOfBlock);

			// Attach to this actor
			NewBlock->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			// Tell the block about its owner
			if (NewBlock != nullptr)
			{
				NewBlock->bIsPressed = false;
				NewBlock->OwningBoard = this;
			}
		}
	}
	//SpawnRandomShips();
}

// Called every frame
void ABattleShipBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABlock * ABattleShipBoard::GetBlockByIndex(int32 Index) const
{
	ABlock* Block = Cast<ABlock>(RootComponent->GetChildComponent(Index)->GetOwner());

	return Block;
}

int32 ABattleShipBoard::CalculateIndex(int32 X, int32 Y)
{
	// return an index from 0 to (Size * Size)
	return X + (Size * Y);
}

FVector ABattleShipBoard::CalculateLocation(int32 Index)
{
	float X_Offset = (Index / Size) * BlockSpacing; // Divide by dimension
	float Y_Offset = (Index % Size) * BlockSpacing; // Modulo gives remainder

	return FVector(X_Offset, Y_Offset, 0.0f);
}

/*
void ABattleShipBoard::SpawnRandomShips()
{
	FVector location = CalculateLocation(0) + GetActorLocation();
	//ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(location, FRotator(0.0f, 0.0f, 0.0f));
	//TWeakObjectPtr<UMaterialInstanceDynamic> Material = NewBlock->GetBlockMesh()->CreateAndSetMaterialInstanceDynamic(0);
	//Material->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(1.0f, 0.0f, 0.0f));
	//NewBlock->GetBlockMesh()->SetRelativeScale3D(FVector(0.3f, 0.6f, 0.1f));
	TWeakObjectPtr<AShip> NewShip = GetWorld()->SpawnActor<AShip>(location, FRotator(0.0f, 45.0f, 90.0f));
	NewShip->GetShipMesh()->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));
}
*/