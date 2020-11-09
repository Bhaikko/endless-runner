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

public:
	virtual void Tick(float DeltaTime) override;

private:
	void MoveDown();
	
};
