// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameState.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API USaveGameState : public USaveGame
{
	GENERATED_BODY()

public:
	USaveGameState();

private:
	int32 HighScore;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetHighScore() const { return HighScore; }

public:
	void SetHighScore(int32 NewHighScore);
	
};
