// Fill out your copyright notice in the Description page of Project Settings.


#include "WallRunning.h"
#include "Components/ArrowComponent.h"

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
}

void AWallRunning::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void AWallRunning::SpawnObstacleInLane(class UArrowComponent* Lane) 
{
    
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
