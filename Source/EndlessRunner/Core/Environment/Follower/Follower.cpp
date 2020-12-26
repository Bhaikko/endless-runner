// Fill out your copyright notice in the Description page of Project Settings.


#include "Follower.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerCharacter.h"

// Sets default values
AFollower::AFollower()
{
	PrimaryActorTick.bCanEverTick = true;

	FollowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FollowerMesh"));
	bShouldFollow = true;

	ChaseSpeed = 100.0f;
}

// Called when the game starts or when spawned
void AFollower::BeginPlay()
{
	Super::BeginPlay();

	RunnerCharacterReference = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardsPlayer(DeltaTime);
}

void AFollower::MoveTowardsPlayer(float DeltaTime) 
{
	float CurrentX = GetActorLocation().X;

	if (bShouldFollow) {
		SetActorLocation(FVector(
			FMath::FInterpConstantTo(CurrentX, RunnerCharacterReference->GetActorLocation().X, DeltaTime, ChaseSpeed),
			RunnerCharacterReference->GetActorLocation().Y + 0.0f,
			RunnerCharacterReference->GetActorLocation().Z
		));
	}
	
}

void AFollower::Destroy() 
{
	Destroy();
}

void AFollower::StopFollowing() 
{
	bShouldFollow = false;

	FTimerHandle DestroyHandler;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandler, this, &AFollower::Destroy, 0.0f);
}

