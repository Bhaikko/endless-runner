// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"
#include "GlidingTiles.generated.h"

UCLASS()
class ENDLESSRUNNER_API AGlidingTiles : public AMasterTile
{
	GENERATED_BODY()

public:
	AGlidingTiles();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane0;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane1;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane2;
	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane3;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane4;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane5;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane6;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane7;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane8;

private:
	UFUNCTION()
	void SpawnObstaclesInLane(UArrowComponent* Lane);

protected:
	virtual void SpawnObstacles() override;

public:
	virtual TArray<FVector> GetLanes() override;
	
};
