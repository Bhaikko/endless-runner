// Fill out your copyright notice in the Description page of Project Settings.


#include "LaneHandler.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"

// Sets default values for this component's properties
ULaneHandler::ULaneHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentLaneY = 1;
	CurrentLaneZ = 1;

	ChangeLaneSpeed = 100.0f;
}


// Called when the game starts
void ULaneHandler::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	RunnerCharacterReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MovementComponent = Cast<UCharacterMovementComponent>(RunnerCharacterReference->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	
	// Lanes.Push(FVector());
	UpdateLanes();
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
	if (Lanes.Num() < 9) {
		return;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = Lanes[NewLaneZ * 3 + NewLaneY];

	if (GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::WALLRUNNING) {
		GetOwner()->SetActorLocation(FVector(
			CurrentLocation.X,
			FMath::FInterpConstantTo(CurrentLocation.Y, NewLocation.Y, DeltaTime, ChangeLaneSpeed),
			FMath::FInterpConstantTo(CurrentLocation.Z, NewLocation.Z, DeltaTime, ChangeLaneSpeed)
		));
	} else {
		GetOwner()->SetActorLocation(FVector(
			CurrentLocation.X,
			FMath::FInterpConstantTo(CurrentLocation.Y, NewLocation.Y, DeltaTime, ChangeLaneSpeed),
			CurrentLocation.Z
		));
	}


	float Distance = FMath::Abs(CurrentLocation.Y - NewLocation.Y);

	if (Distance <= 5.0f) {
		bShouldSwitch = false;
	} 
	
}

void ULaneHandler::UpdateLanes() 
{
	Lanes = GameModeReference->GetLaneVectors();

	if (GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::WALLRUNNING) {
		RunnerCharacterReference->SetWallRunning(true);
		MovementComponent->GravityScale = 0.0f;
	} else {
		MovementComponent->GravityScale = 1.0f;
	}
}

void ULaneHandler::ChangeLane(EndlessRunnerEnums::EMovementDirection Direction) 
{

	if (Direction == EndlessRunnerEnums::EMovementDirection::LEFT) {
		MoveLeft();
	} else if (Direction == EndlessRunnerEnums::EMovementDirection::RIGHT) {
		MoveRight();
	} 
	
	if (Direction == EndlessRunnerEnums::EMovementDirection::UP) {
		MoveUp();
	} else if (Direction == EndlessRunnerEnums::EMovementDirection::DOWN) {
		MoveDown();
	}

	bShouldSwitch = true;

}

void ULaneHandler::MoveLeft() 
{
	switch (GameModeReference->GetCurrentTileType()) {
		case EndlessRunnerEnums::ETilesType::RUNNING:
			NewLaneY = FMath::Clamp<float>(
				CurrentLaneY - 1,
				0,
				2
			);
			CurrentLaneY = NewLaneY;
			NewLaneZ = CurrentLaneZ;
			break;

		case EndlessRunnerEnums::ETilesType::WALLRUNNING:
			NewLaneY = FMath::Clamp<float>(
				CurrentLaneY - 1,
				0, 
				1
			);
			CurrentLaneY = NewLaneY;
			NewLaneZ = CurrentLaneZ;

			// RunnerCharacterReference->SetWallRunning(false);

			break;

		case EndlessRunnerEnums::ETilesType::GLIDING:

			break;

		default:
			break;
	}
}

void ULaneHandler::MoveRight() 
{
		
	switch (GameModeReference->GetCurrentTileType()) {
		case EndlessRunnerEnums::ETilesType::RUNNING:
			NewLaneY = FMath::Clamp<float>(
				CurrentLaneY + 1,
				0,
				2
			);
			CurrentLaneY = NewLaneY;
			NewLaneZ = CurrentLaneZ;
			break;

		case EndlessRunnerEnums::ETilesType::WALLRUNNING:
			NewLaneY = FMath::Clamp<float>(
				CurrentLaneY + 1,
				0, 
				1
			);
			CurrentLaneY = NewLaneY;
			NewLaneZ = CurrentLaneZ;
			// RunnerCharacterReference->SetWallRunning(false);

			
			break;

		case EndlessRunnerEnums::ETilesType::GLIDING:

			break;

		default:
			break;
	}
}

void ULaneHandler::MoveUp() 
{
	
}

void ULaneHandler::MoveDown() 
{
	
}

