// Fill out your copyright notice in the Description page of Project Settings.


#include "WallRunning.h"
#include "Components/ArrowComponent.h"

#include "EndlessRunner/Core/Environment/Obstacle/Obstacle.h"
#include "EndlessRunner/Core/Environment/Pickup/Pickup.h"

AWallRunning::AWallRunning() 
{
    LeftWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Wall"));
    LeftWall->SetupAttachment(Root);

    RightWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Wall"));
    RightWall->SetupAttachment(Root);

	// Left Lane
	Lane0 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane0"));
	Lane0->SetupAttachment(Root);

	// Right lane
	Lane1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane2"));
	Lane1->SetupAttachment(Root);  

}

void AWallRunning::BeginPlay() 
{
    Super::BeginPlay();
    DespawnOneWall();

    SpawnObstacles();
}

void AWallRunning::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void AWallRunning::SpawnObstacleInLane(class UArrowComponent* Lane) 
{
    // Flyers, Magnet and coins spawnable
    if (
        !ObstacleClasses[EObstacle::FLYER] ||
        !ObstacleClasses[EPickup::COIN] ||
        !ObstacleClasses[EPickup::MAGNET]
    ) {
        UE_LOG(LogTemp, Warning, TEXT("One of Obstacle or Pickup class Missing"));
        return;
    }

    float ChanceOfSpawning = FMath::RandRange(0.0f, 1.0f);
    FVector Offset = FVector(0.0f, 0.0f, 600.0f);

    if (ChanceOfSpawning >= 0.1f && ChanceOfSpawning <= 0.2f) {
		AObstacle* SpawnedRunner = GetWorld()->SpawnActor<AObstacle>(
			ObstacleClasses[EObstacle::FLYER],
			Lane->GetComponentLocation() + Offset,
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.2f && ChanceOfSpawning <= 0.7f) {
		APickup* SpawnedCoin = GetWorld()->SpawnActor<APickup>(
			PickupClasses[EPickup::COIN],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
		
	} else if (ChanceOfSpawning > 0.9f && ChanceOfSpawning <= 1.0f) {
		APickup* SpawnedCoin = GetWorld()->SpawnActor<APickup>(
			PickupClasses[EPickup::MAGNET],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	}
}

void AWallRunning::DespawnOneWall() 
{
    float ChanceOfSpawning = FMath::RandRange(0.0f, 1.0f);

    if (ChanceOfSpawning <= 0.40f) {
        float WallProb = FMath::RandRange(0.0f, 1.0f);

        if (WallProb >= 0.5f) {
            LeftWall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            LeftWall->SetVisibility(false);
        } else {
            RightWall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            RightWall->SetVisibility(false);
        }
    }
}

void AWallRunning::SpawnObstacles() 
{
    SpawnObstacleInLane(Lane0);
    SpawnObstacleInLane(Lane1);
}

TArray<FVector> AWallRunning::GetLanes() 
{
    TArray<FVector> Locations;
	for (int i = 0; i < 9; i++) {
		Locations.Push(FVector());
	}

	Locations[3] = Lane0->GetComponentLocation();
	Locations[4] = Lane1->GetComponentLocation();

	return Locations;
}
