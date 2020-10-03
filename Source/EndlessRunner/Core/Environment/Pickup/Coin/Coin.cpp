// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"


void ACoin::BeginPlay() 
{
    Super::BeginPlay();

    PickupMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnPickup);
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
}
