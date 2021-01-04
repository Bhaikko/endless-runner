// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunner/Core/Resources/Enums.h"
#include "EndlessRunner/Core/Resources/SaveGameHandler/SaveGameHandler.h"
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

protected:

	/*
		0 -> Running
		1 -> Wall Running
		2 -> Gliding
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Tiles Configuration")
	TArray<TSubclassOf<class AMasterTile>> TileClasses;	

private:
	FVector NextSpawnPointLocation;

	// Point System, Everytime player runs over tile, it scores a Point
	int32 Points;
	int32 PointsMultiplier;
	int32 Coins;

public:
	void IncreaseScore(int32 ScoreToAdd);
	void IncreaseCoins(int32 CoinsToAdd);
	void TrySetNewHighScore();

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetScore() const { return Points; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCoins() const { return Coins; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetHighScore() const { return SaveGameHandler->GetHighScore(); }

	FORCEINLINE EndlessRunnerEnums::ETilesType GetCurrentTileType() const { return CurrentTiles; }

	TArray<FVector> GetLaneVectors();

	class UArrowComponent* GetTileComponentBeforeChanged();

	void PopSpawnPoint();


private:
	ASaveGameHandler* SaveGameHandler;

	EndlessRunnerEnums::ETilesType CurrentTiles;
	class AMasterTile* CurrentSpawnedTile;

	TQueue<class UArrowComponent*> TileComponentBeforeChangedQueue;

private:
	UFUNCTION()
	void FindReferenceOfSaveGameHandler();

	UFUNCTION()
	void ChangeTiles();

	UFUNCTION()
	void DeleteFollower();

};



