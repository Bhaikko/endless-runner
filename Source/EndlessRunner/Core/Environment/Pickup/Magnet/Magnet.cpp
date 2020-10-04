// Fill out your copyright notice in the Description page of Project Settings.


#include "Magnet.h"

#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"


AMagnet::AMagnet() 
{
    PickupDuration = 10.0f;   
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

    UE_LOG(LogTemp, Warning, TEXT("Magnet Active"));

    FTimerHandle PickupDurationHandle;
    GetWorld()->GetTimerManager().SetTimer(PickupDurationHandle, this, &AMagnet::DisableAbility, PickupDuration);

    Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}

void AMagnet::DisableAbility() 
{
    AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!RunnerCharacter) {
		return;
	}

    RunnerCharacter->SetMagnetStatus(false);
    UE_LOG(LogTemp, Warning, TEXT("Magnet deactivated"));

    Destroy();
}
