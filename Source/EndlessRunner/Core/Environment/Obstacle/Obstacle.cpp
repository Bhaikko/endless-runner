// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

