// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"
#include "Components/ArrowComponent.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	NextSpawnPointLocation = FVector(0.0f, 0.0f, 0.0f);
}

void AEndlessRunnerGameMode::BeginPlay() 
{
	for (uint32 i = 1; i <= 10; i++) {
		SpawnTile();
	}	
}

void AEndlessRunnerGameMode::SpawnTile() 
{
	if (!TileClass) {
		UE_LOG(LogTemp, Warning, TEXT("No Tile class Specified!!"));
		return;
	}

	AMasterTile* SpawnedTile = GetWorld()->SpawnActor<AMasterTile>(
		TileClass,
		NextSpawnPointLocation,
		FRotator(0.0f, 0.0f, 0.0f)
	);

	NextSpawnPointLocation = SpawnedTile->GetSpawnPoint()->GetComponentLocation();
}
