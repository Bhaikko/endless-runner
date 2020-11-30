// Fill out your copyright notice in the Description page of Project Settings.


#include "GlidingTiles.h"

#include "Components/ArrowComponent.h"


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
}

void AGlidingTiles::BeginPlay() 
{
    Super::BeginPlay();
}

void AGlidingTiles::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void AGlidingTiles::SpawnObstaclesInLane(UArrowComponent* Lane) 
{
    
}

void AGlidingTiles::SpawnObstacles() 
{
    
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
