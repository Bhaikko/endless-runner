// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/MasterTile/MasterTile.h"
#include "WallRunning.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AWallRunning : public AMasterTile
{
	GENERATED_BODY()

public:
	AWallRunning();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftWall;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* MiddleWall;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightWall;

private:
	UFUNCTION()
	void SpawnObstacleInLane(class UArrowComponent* Lane);

	UFUNCTION()
	void SpawnMiddleWall();

protected:
	virtual void SpawnObstacles() override;

public:
	virtual TArray<FVector> GetLanes() override;
	
};
