// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/Obstacle/Obstacle.h"
#include "Runner.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunner : public AObstacle
{
	GENERATED_BODY()

public:	
	ARunner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class TSubclassOf<UAnimInstance> JumpingAnimation;

private:
	FVector JumpPos;
	
};
