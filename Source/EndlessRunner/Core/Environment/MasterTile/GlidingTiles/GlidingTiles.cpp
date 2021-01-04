// Fill out your copyright notice in the Description page of Project Settings.


#include "GlidingTiles.h"

#include "Components/ArrowComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/Core/Environment/Obstacle/Obstacle.h"
#include "EndlessRunner/Core/Environment/Pickup/Pickup.h"


AGlidingTiles::AGlidingTiles() 
{
    Lane0 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane0"));
	Lane0->SetupAttachment(Root);

    Lane1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane1"));
	Lane1->SetupAttachment(Root);

    Lane2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane2"));
	Lane2->SetupAttachment(Root);
    
    Lane3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane3"));
	Lane3->SetupAttachment(Root);

    Lane4 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane4"));
	Lane4->SetupAttachment(Root);

    Lane5 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane5"));
	Lane5->SetupAttachment(Root);

    Lane6 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane6"));
	Lane6->SetupAttachment(Root);

    Lane7 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane7"));
	Lane7->SetupAttachment(Root);

    Lane8 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane8"));
	Lane8->SetupAttachment(Root);

    Point0 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point0"));
	Point0->SetupAttachment(Root);

    Point1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point1"));
	Point1->SetupAttachment(Root);
    
    Point3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point3"));
	Point3->SetupAttachment(Root);

    Point2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point2"));
	Point2->SetupAttachment(Root);

    Point4 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point4"));
	Point4->SetupAttachment(Root);

    Point5 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point5"));
	Point5->SetupAttachment(Root);

    Point6 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point6"));
	Point6->SetupAttachment(Root);

    DistanceBetween = 9000.0f;
    bSpawned = false;


}

void AGlidingTiles::BeginPlay() 
{
    Super::BeginPlay();

    PlayerReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    SpawnPickup();

}

void AGlidingTiles::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (bSpawned) {
        return;
    }

    DistanceBetween = GetActorLocation().X - PlayerReference->GetActorLocation().X;
    if (DistanceBetween <= 1500.0f) {
        AEndlessRunnerGameMode* GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    
        if (GameMode->GetScore() >= 2) {
            SpawnObstacles();	

        }
        

        bSpawned = true;
    }
}

void AGlidingTiles::SpawnObstaclesInLane(UArrowComponent* Lane) 
{
    if (
		!ObstacleClasses[EObstacle::GLIDEHANDS] 
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
	FVector Offset = FVector(0.0f, 0.0f, 60.0f);

	if (ChanceOfSpawning >= 0.1f && ChanceOfSpawning <= 0.3f) {
		AObstacle* SpawnedHand = GetWorld()->SpawnActor<AObstacle>(
			ObstacleClasses[EObstacle::RUNNER],
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);

       
	} 
}

void AGlidingTiles::SpawnPickupInLane(UArrowComponent* Lane) 
{
    if (
		!PickupClasses[EPickup::COIN] || 
        !PickupClasses[EPickup::MAGNET] 
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
	FVector Offset = FVector(0.0f, 0.0f, 60.0f);

	if (ChanceOfSpawning >= 0.1f && ChanceOfSpawning <= 0.5f) {
        APickup* Pickup = GetWorld()->SpawnActor<APickup>(
            PickupClasses[EPickup::COIN],
            Lane->GetComponentLocation(),
            Lane->GetComponentRotation()
        );
	} else if (ChanceOfSpawning >= 0.5f && ChanceOfSpawning <= 0.6f) {
        APickup* Pickup = GetWorld()->SpawnActor<APickup>(
            PickupClasses[EPickup::MAGNET],
            Lane->GetComponentLocation(),
            Lane->GetComponentRotation()
        );
	}
}

void AGlidingTiles::SpawnObstacles() 
{
    SpawnObstaclesInLane(Point1);
    SpawnObstaclesInLane(Point2);
    SpawnObstaclesInLane(Point3);
    SpawnObstaclesInLane(Point4);
    SpawnObstaclesInLane(Point5);
    SpawnObstaclesInLane(Point6);
}

void AGlidingTiles::SpawnPickup() 
{
    SpawnPickupInLane(Lane0);
    SpawnPickupInLane(Lane1);
    SpawnPickupInLane(Lane2);
    SpawnPickupInLane(Lane3);
    SpawnPickupInLane(Lane4);
    SpawnPickupInLane(Lane5);
    SpawnPickupInLane(Lane6);
    SpawnPickupInLane(Lane7);
    SpawnPickupInLane(Lane8);
}

TArray<FVector> AGlidingTiles::GetLanes() 
{
    TArray<FVector> Locations;

    for (int i = 0; i < 9; i++) {
		Locations.Push(FVector());
	}

    Locations[0] = Lane0->GetComponentLocation();
    Locations[1] = Lane1->GetComponentLocation();
    Locations[2] = Lane2->GetComponentLocation();

    Locations[3] = Lane3->GetComponentLocation();
    Locations[4] = Lane4->GetComponentLocation();
    Locations[5] = Lane5->GetComponentLocation();

    Locations[6] = Lane6->GetComponentLocation();
    Locations[7] = Lane7->GetComponentLocation();
    Locations[8] = Lane8->GetComponentLocation();

    return Locations;
}
