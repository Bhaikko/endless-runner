// Fill out your copyright notice in the Description page of Project Settings.


#include "LaneHandler.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"

// Sets default values for this component's properties
ULaneHandler::ULaneHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentLaneY = 1;
	CurrentLaneZ = 1;

	for (int i = 0; i < 9; i++) {
		Lanes.Push(FVector());
	}

	ChangeLaneSpeed = 100.0f;
}


// Called when the game starts
void ULaneHandler::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	RunnerCharacterReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	ChangeTiles(ETilesType::RUNNING);	
}


// Called every frame
void ULaneHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShouldSwitch) {
		LerpBetweenLanes(DeltaTime);
	}
}

void ULaneHandler::LerpBetweenLanes(float DeltaTime) 
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = Lanes[NewLaneZ * 3 + NewLaneY];
	
	GetOwner()->SetActorLocation(FVector(
		CurrentLocation.X,
		FMath::FInterpConstantTo(CurrentLocation.Y, NewLocation.Y, DeltaTime, ChangeLaneSpeed),
		FMath::FInterpConstantTo(CurrentLocation.Z, NewLocation.Z, DeltaTime, ChangeLaneSpeed)
	));


	if (FVector::Distance(NewLocation - CurrentLocation) <= 0.01f) {
		bShouldSwitch = false;
	} 
}

void ULaneHandler::ChangeTiles(ETilesType TilesType) 
{
	GameModeReference->GetLaneVectors(Lanes, TilesType);

}

void ULaneHandler::ChangeLane(EMovementDirection Direction) 
{
	if (Direction == EMovementDirection::LEFT) {
		MoveLeft();
	} else if (Direction == EMovementDirection::RIGHT) {
		MoveRight();
	} 
	
	if (Direction == EMovementDirection::UP) {
		MoveUp();
	} else if (Direction == EMovementDirection::DOWN) {
		MoveDown();
	}

	bShouldSwitch = true;

}

void ULaneHandler::MoveLeft() 
{
	if (GameModeReference->GetCurrentTileType() == ETilesType::RUNNING) {
		NewLaneY = FMath::Clamp<float>(
			CurrentLaneY - 1,
			0,
			1
		);

		NewLaneZ = CurrentLaneZ;
	}

}

void ULaneHandler::MoveRight() 
{
	if (GameModeReference->GetCurrentTileType() == ETilesType::RUNNING) {
		NewLaneY = FMath::Clamp<float>(
			CurrentLaneY + 1,
			0,
			2
		);

		NewLaneZ = CurrentLaneZ;
	}
}

