// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

#include "EndlessRunner/EndlessRunnerCharacter.h"


// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bMoveTowardsPlayer = false;

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnHit);

	PlayerReference = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerReference) {
		float DistanceBetween = PlayerReference->GetActorLocation().X - GetActorLocation().X;
		if (DistanceBetween >= 500.0f) {
			Destroy();
		}

		MoveTowardsPlayer();
	}

}

void AObstacle::OnHit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

	CollidedActor->HandleDeath();
}

void AObstacle::MoveTowardsPlayer() 
{
	AddMovementInput(FVector(-1.0f, 0.0f, 0.0f), 1.0f, true);
	
}

