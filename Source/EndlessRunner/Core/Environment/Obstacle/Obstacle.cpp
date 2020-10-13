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

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	CapsuleCollider->SetupAttachment(Root);
	CapsuleCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	ObstacleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnHit);

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
	}

}

void AObstacle::OnHit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

	// CollidedActor->HandleDeath();
}

