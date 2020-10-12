// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

#include "EndlessRunner/EndlessRunnerCharacter.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ObstacleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(Root);
	ObstacleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	ObstacleMesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnHit);
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OnHit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

	CollidedActor->HandleDeath();
}

