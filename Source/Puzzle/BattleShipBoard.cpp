// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleShipBoard.h"
#include "PuzzleBlock.h"

// Sets default values
ABattleShipBoard::ABattleShipBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Loop to spawn each block that compose the board
	for (int32 Y_Index = 0; Y_Index < Size; Y_Index++) 
	{
		for (int32 X_Index = 0; X_Index < Size; X_Index++)
		{
			// Obtain the index of the block
			int32 Index = CalculateIndex(X_Index, Y_Index);

			// Make position vector
			const FVector location = CalculateLocation(X_Index, Y_Index);

			// Spawn block
			//APuzzleBlock* block = GetWorld()->SpawnActor<APuzzleBlock>(location, FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

// Called when the game starts or when spawned
void ABattleShipBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleShipBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ABattleShipBoard::CalculateIndex(int32 X, int32 Y)
{
	return X + (Size * Y);
}

FVector ABattleShipBoard::CalculateLocation(int32 X, int32 Y)
{
	return FVector();
}

