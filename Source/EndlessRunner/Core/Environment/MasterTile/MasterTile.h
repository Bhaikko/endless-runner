// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterTile.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMasterTile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane0;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane1;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Lane2;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* SpawnPoint;

	// Responsible for Spawning Successive tile once player Overlaps this component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;
	
private:
	FTimerHandle DestroyTileHandle;

public:	
	// Sets default values for this actor's properties
	AMasterTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Delegates
private:
	UFUNCTION()
	void TileSpawnHandler(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// Getters
public:
	UArrowComponent* GetSpawnPoint() const;

private:
	UFUNCTION()
	void HandleDestruction();

	UFUNCTION()
	void SpawnObstacles();

	UFUNCTION()
	void SpawnObstacleInLane(UArrowComponent* Lane);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Obstacles")
	TSubclassOf<class AObstacle> PipeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Obstacles")
	TSubclassOf<class AObstacle> BoxClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TSubclassOf<class APickup> CoinClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TSubclassOf<class APickup> MagnetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TSubclassOf<class APickup> JumpBootClass;

};
