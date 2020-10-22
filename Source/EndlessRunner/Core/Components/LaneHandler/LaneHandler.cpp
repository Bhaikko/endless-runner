// Fill out your copyright notice in the Description page of Project Settings.


#include "LaneHandler.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"

// Sets default values for this component's properties
ULaneHandler::ULaneHandler()
{
	PrimaryComponentTick.bCanEverTick = true;

	Lanes = nullptr;
}


// Called when the game starts
void ULaneHandler::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	RunnerCharacterReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	
}


// Called every frame
void ULaneHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULaneHandler::ChangeTiles(enum ETilesType TilesType) 
{
	// Lanes = 
}

void ULaneHandler::ChangeLane(EMovementDirection Direction) 
{
	
}

