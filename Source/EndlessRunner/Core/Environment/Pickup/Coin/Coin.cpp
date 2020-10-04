// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"

ACoin::ACoin()
{
    MagnetActiveCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Magnet Active Collider"));
    MagnetActiveCollider->SetupAttachment(Root);
    PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    bAttractToPlayer = false;
}

void ACoin::BeginPlay() 
{
    Super::BeginPlay();

    PickupMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnPickup);
    MagnetActiveCollider->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnMagnetActive);

}

void ACoin::OnPickup(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
    AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

    Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    AEndlessRunnerGameMode* GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode) {
        UE_LOG(LogTemp, Warning, TEXT("Game Mode null in Coin class"));
        return;
    }
    GameMode->IncreaseCoins(1);
    Destroy();
}

void ACoin::Tick(float DeltaTime) 
{
    if (bAttractToPlayer) {
        AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        SetActorLocation(FMath::Lerp<FVector>(GetActorLocation(), RunnerCharacter->GetActorLocation(), 0.5f));
    }
}

void ACoin::OnMagnetActive(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
    AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

    if (!CollidedActor->IsMagnetActive()) {
        return;
    }

    bAttractToPlayer = true;

}
