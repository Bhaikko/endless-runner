// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameMode();

public:
	void SpawnTile();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Tiles Configuration", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMasterTile> TileClass;

private:
	FVector NextSpawnPointLocation;

};



