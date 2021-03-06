// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	PickupMesh->SetupAttachment(Root);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Component"));

	PickupDuration = 0.0f;

	bPicked = false;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerReference = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bPicked) {
		if (PlayerReference) {
			float DistanceBetween = PlayerReference->GetActorLocation().X - GetActorLocation().X;
			if (DistanceBetween >= 500.0f) {
				Destroy();
			}
		}
	}

}

void APickup::OnPickup(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetVisibility(false);

	bPicked = true;

	if (!PickupSound) {
		UE_LOG(LogTemp, Warning, TEXT("No Pickup sound assigned"));
	} else {
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation(),
			0.7f,
			0.0f
		);
	}
}

void APickup::OnDisableAbility() 
{
	Destroy();
}

