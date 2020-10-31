// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterTile.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMasterTile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* SpawnPoint;

	// Responsible for Spawning Successive tile once player Overlaps this component
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	// Responsible for Falling Death
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* DeathCollider;
	
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
	virtual void TileSpawnHandler(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void FallHandler(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// Getters
public:
	UArrowComponent* GetSpawnPoint() const;

	virtual void GetLanes(TArray<FVector>& Locations);

protected:
	UFUNCTION()
	void HandleDestruction();

	UFUNCTION()
	virtual void SpawnObstacles();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Obstacles")
	TArray<TSubclassOf<class AObstacle>> ObstacleClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TArray<TSubclassOf<class APickup>> PickupClasses;

protected:
	enum EObstacle 
	{
		RUNNER = 0,
		STONEGUY,
		HANDS
	};

	enum EPickup
	{
		COIN = 0,
		MAGNET,
		BOOTS
	};
	

};
