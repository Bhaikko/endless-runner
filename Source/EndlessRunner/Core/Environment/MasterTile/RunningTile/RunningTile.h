// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"
#include "RunningTile.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API ARunningTile : public AMasterTile
{
	GENERATED_BODY()

public:
	ARunningTile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Road;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane0;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane1;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UArrowComponent* Lane2;

private:
	UFUNCTION()
	void SpawnObstacleInLane(UArrowComponent* Lane);

protected:
	virtual void SpawnObstacles() override;

public:
	virtual FVector* GetLanes() override;
};
