// Fill out your copyright notice in the Description page of Project Settings.


#include "WallRunning.h"


AWallRunning::AWallRunning() 
{
    LeftWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Wall"));
    LeftWall->SetupAttachment(Root);

    MiddleWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle Wall"));
    MiddleWall->SetupAttachment(Root);

    RightWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Wall"));
    RightWall->SetupAttachment(Root);
}

void AWallRunning::BeginPlay() 
{
    Super::BeginPlay();
    SpawnMiddleWall();
}

void AWallRunning::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void AWallRunning::SpawnObstacleInLane(class UArrowComponent* Lane) 
{
    
}

void AWallRunning::SpawnMiddleWall() 
{
    float ChanceOfSpawning = FMath::RandRange(0.0f, 1.0f);

    if (ChanceOfSpawning <= 0.25f) {
        MiddleWall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        MiddleWall->SetVisibility(false);
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

	Locations[3] = LeftWall->GetComponentLocation();
	Locations[4] = MiddleWall->GetComponentLocation();
	Locations[5] = RightWall->GetComponentLocation();

	return Locations;
}
