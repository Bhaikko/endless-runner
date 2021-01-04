// Fill out your copyright notice in the Description page of Project Settings.


#include "LaneHandler.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "EndlessRunner/Core/Environment/Follower/Follower.h"

// Sets default values for this component's properties
ULaneHandler::ULaneHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentLaneY = 1;
	CurrentLaneZ = 1;

	ChangeLaneSpeed = 100.0f;
	RayTraceRange = 10.0f;
}


// Called when the game starts
void ULaneHandler::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	RunnerCharacterReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MovementComponent = Cast<UCharacterMovementComponent>(RunnerCharacterReference->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	
	UpdateLanes();
}


// Called every frame
void ULaneHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RunnerCharacterReference->IsDead()) {
		return;
	}

	if (bShouldSwitch) {
		LerpBetweenLanes(DeltaTime);
	}

	if (
		GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::WALLRUNNING &&
		RunnerCharacterReference->IsWallRunning()
	) {
		FVector Direction = FVector(0.0f, -1.0f, 0.0f);	// Left
		if (RunnerCharacterReference->GetActorLocation().Y > 0.0f) {
			Direction.Y = 1.0f;
		}
		WallDetection(Direction);
	}
}

void ULaneHandler::LerpBetweenLanes(float DeltaTime) 
{
	if (Lanes.Num() < 9) {
		return;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = Lanes[NewLaneZ * 3 + NewLaneY];

	if (
		GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::WALLRUNNING || 
		GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::GLIDING
	) {
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


	// float Distance = FMath::Abs(CurrentLocation.Y - NewLocation.Y);
	float Distance = (NewLocation - CurrentLocation).Size();

	if (Distance <= 5.0f) {
		bShouldSwitch = false;
	} 
	
}

void ULaneHandler::UpdateLanes() 
{
	Lanes = GameModeReference->GetLaneVectors();
	RunnerCharacterReference->Jump();

	if (GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::RUNNING) {
		RunnerCharacterReference->SetWallRunning(false);
		RunnerCharacterReference->SetGliding(false);
		MovementComponent->GravityScale = 1.0f;
	} else {
		MovementComponent->GravityScale = 0.0f;
		if (GameModeReference->GetCurrentTileType() == EndlessRunnerEnums::ETilesType::WALLRUNNING) {
			RunnerCharacterReference->SetWallRunning(true);
			RunnerCharacterReference->SetGliding(false);
		} else {
			RunnerCharacterReference->SetGliding(true);
			RunnerCharacterReference->SetWallRunning(false);

			if (!SpawnedFollower) {
				SpawnedFollower = GetWorld()->SpawnActor<AFollower>(
					FollowerClass,
					RunnerCharacterReference->GetActorLocation() + FVector(-50.0f, -50.0f, -50.0f),
					FRotator(0.0f, -90.0f, 0.0f)
				);
			}
		}
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
			NewLaneY = FMath::Clamp<float>(
				CurrentLaneY - 1,
				0,
				2
			);

			CurrentLaneY = NewLaneY;

			NewLaneZ = CurrentLaneZ;
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
			NewLaneY = FMath::Clamp<float>(
				CurrentLaneY + 1,
				0,
				2
			);

			CurrentLaneY = NewLaneY;
			NewLaneZ = CurrentLaneZ;
			break;

		default:
			break;
	}
}

void ULaneHandler::MoveUp() 
{
	switch (GameModeReference->GetCurrentTileType()) {
		case EndlessRunnerEnums::ETilesType::GLIDING:
			NewLaneY = CurrentLaneY;

			NewLaneZ = FMath::Clamp<float>(
				CurrentLaneZ - 1,
				0,
				2
			);

			CurrentLaneZ = NewLaneZ;

			break;

		default:
			break;
	}
}

void ULaneHandler::MoveDown() 
{
	switch (GameModeReference->GetCurrentTileType()) {
		case EndlessRunnerEnums::ETilesType::GLIDING:
			NewLaneY = CurrentLaneY;

			NewLaneZ = FMath::Clamp<float>(
				CurrentLaneZ + 1,
				0,
				2
			);

			CurrentLaneZ = NewLaneZ;

			break;

		default:
			break;
	}
}

void ULaneHandler::WallDetection(FVector Direction) 
{
	FHitResult HitResult;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(RunnerCharacterReference);

	FVector Start = RunnerCharacterReference->GetActorLocation();
	FVector End = Start + Direction * RayTraceRange;

	// DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);

	bool HadCollision = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Pawn, Params);

	if (!HadCollision) {
		// TODO, Handle Death when Switching
		// UE_LOG(LogTemp, Warning, TEXT("Killing Player"));
		// RunnerCharacterReference->HandleDeath();
	} 
}

