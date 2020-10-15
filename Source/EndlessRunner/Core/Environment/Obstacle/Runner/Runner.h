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

private:
	bool bJumping;

private:
	FVector JumpPos;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsJumping() const { return bJumping; }
	
};
