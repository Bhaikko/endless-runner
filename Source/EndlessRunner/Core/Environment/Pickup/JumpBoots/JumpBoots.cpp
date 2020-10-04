// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpBoots.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"

AJumpBoots::AJumpBoots() 
{
    PickupDuration = 10.0f;   
}

void AJumpBoots::BeginPlay() 
{
    Super::BeginPlay();

    PickupMesh->OnComponentBeginOverlap.AddDynamic(this, &AJumpBoots::OnPickup);
}

void AJumpBoots::OnPickup(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
    AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

    UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(CollidedActor->GetMovementComponent());
    MovementComponent->JumpZVelocity = 1200.0f;


    FTimerHandle PickupDurationHandle;
    GetWorld()->GetTimerManager().SetTimer(PickupDurationHandle, this, &AJumpBoots::DisableAbility, PickupDuration);

    Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);


}

void AJumpBoots::DisableAbility() 
{
    AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!RunnerCharacter) {
		return;
	}

    UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    MovementComponent->JumpZVelocity = 600.0f;


    Destroy();
}
