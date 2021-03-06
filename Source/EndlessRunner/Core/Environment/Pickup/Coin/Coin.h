// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/Pickup/Pickup.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API ACoin : public APickup
{
	GENERATED_BODY()

public:
	ACoin();
	
protected:
	virtual void BeginPlay() override;

	virtual void OnPickup(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void Tick(float DeltaTime);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USphereComponent* MagnetActiveCollider;

protected:
	UFUNCTION()
	void OnMagnetActive(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bAttractToPlayer;

};
