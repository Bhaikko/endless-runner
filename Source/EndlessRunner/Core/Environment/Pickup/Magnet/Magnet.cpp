// Fill out your copyright notice in the Description page of Project Settings.


#include "Magnet.h"

#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"


AMagnet::AMagnet() 
{
     
}

void AMagnet::BeginPlay() 
{
    Super::BeginPlay();

    PickupMesh->OnComponentBeginOverlap.AddDynamic(this, &AMagnet::OnPickup);
}

void AMagnet::OnPickup(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
    AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

    CollidedActor->SetMagnetStatus(true);


    FTimerHandle PickupDurationHandle;
    GetWorld()->GetTimerManager().SetTimer(PickupDurationHandle, this, &AMagnet::OnDisableAbility, PickupDuration);

    Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}

void AMagnet::OnDisableAbility() 
{
    AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!RunnerCharacter) {
		return;
	}

    RunnerCharacter->SetMagnetStatus(false);

    Super::OnDisableAbility();
}
