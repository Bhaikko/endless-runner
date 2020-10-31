// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningTile.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/Core/Environment/Obstacle/Obstacle.h"
#include "EndlessRunner/Core/Environment/Pickup/Pickup.h"


ARunningTile::ARunningTile() 
{
    Road = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Road"));
    Road->SetupAttachment(Root);

    
	// Left Lane
	Lane0 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane0"));
	Lane0->SetupAttachment(Road);

	// Middle Lane
	Lane1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane1"));
	Lane1->SetupAttachment(Road);

	// Right lane
	Lane2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane2"));
	Lane2->SetupAttachment(Road);   
}

void ARunningTile::BeginPlay() 
{
    Super::BeginPlay();

    // Spawning Obstacle 
	AEndlessRunnerGameMode* GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode->GetScore() >= 2) {
		SpawnObstacles();	
	}
}

void ARunningTile::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void ARunningTile::SpawnObstacleInLane(UArrowComponent* Lane) 
{
    if (
		!ObstacleClasses[EObstacle::RUNNER] || 
		!ObstacleClasses[EObstacle::STONEGUY] || 
		!PickupClasses[EPickup::COIN] || 
		!PickupClasses[EPickup::MAGNET] || 
		!PickupClasses[EPickup::BOOTS]
	) {
		UE_LOG(LogTemp, Warning, TEXT("One of Obstacle or Pickup Class Missing."));
		return;
	}

	if (!Lane) {
		UE_LOG(LogTemp, Warning, TEXT("no Lane Found, Intresting"));
		return;
	}

	// Randomly Spawning Obstacle using Random Int 
	float ChanceOfSpawning = FMath::RandRange(0.0f, 1.0f);


	if (ChanceOfSpawning >= 0.1f && ChanceOfSpawning <= 0.2f) {
		AObstacle* SpawnedPipe = GetWorld()->SpawnActor<AObstacle>(
			ObstacleClasses[EObstacle::RUNNER],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.2f && ChanceOfSpawning <= 0.3f) {
		AObstacle* SpawnedBox = GetWorld()->SpawnActor<AObstacle>(
			ObstacleClasses[EObstacle::STONEGUY],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.3f && ChanceOfSpawning <= 0.4f) {
		AObstacle* SpawnedBox = GetWorld()->SpawnActor<AObstacle>(
			ObstacleClasses[EObstacle::HANDS],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.4f && ChanceOfSpawning <= 0.5f) {
		Road->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Road->SetVisibility(false);	
	} else if (ChanceOfSpawning > 0.6f && ChanceOfSpawning <= 0.9f) {
		APickup* SpawnedCoin = GetWorld()->SpawnActor<APickup>(
			PickupClasses[EPickup::COIN],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.9f && ChanceOfSpawning <= 0.95f) {
		APickup* SpawnedMagnet = GetWorld()->SpawnActor<APickup>(
			PickupClasses[EPickup::MAGNET],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.95f && ChanceOfSpawning <= 1.00f) {
		APickup* SpawnedMagnet = GetWorld()->SpawnActor<APickup>(
			PickupClasses[EPickup::BOOTS],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	}
}

void ARunningTile::SpawnObstacles() 
{
    SpawnObstacleInLane(Lane0);
    SpawnObstacleInLane(Lane1);
    SpawnObstacleInLane(Lane2);
}

void ARunningTile::GetLanes(TArray<FVector>& Locations) 
{
	for (int i = 0; i < 9; i++) {
		Locations[i] = FVector();
	}

	Locations[3] = Lane0->GetComponentLocation();
	Locations[4] = Lane1->GetComponentLocation();
	Locations[5] = Lane2->GetComponentLocation();
}
