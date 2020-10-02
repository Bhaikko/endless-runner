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

	// Point System, Everytime player runs over tile, it scores a Point
	int32 Points;
	int32 PointsMultiplier;

public:
	void IncreaseScore(int32 ScoreToAdd);

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetScore() const { return Points; }

};



