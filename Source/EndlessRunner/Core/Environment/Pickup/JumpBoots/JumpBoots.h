// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/Pickup/Pickup.h"
#include "JumpBoots.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AJumpBoots : public APickup
{
	GENERATED_BODY()

public:
	AJumpBoots();

protected:
	virtual void BeginPlay() override;

	virtual void OnPickup(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float PickupDuration;

private:
	UFUNCTION()
	void DisableAbility();
	
};