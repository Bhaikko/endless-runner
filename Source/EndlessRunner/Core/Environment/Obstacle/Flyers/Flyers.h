// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/Obstacle/Obstacle.h"
#include "Flyers.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AFlyers : public AObstacle
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void MoveDown(float DeltaTime);

	class UCharacterMovementComponent* MovementComponent;

protected:
	UPROPERTY(EditDefaultsOnly)
	float DropSpeed;
	
};
