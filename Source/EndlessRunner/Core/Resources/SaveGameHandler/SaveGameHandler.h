// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunner/Core/Resources/SaveGameState/SaveGameState.h"

#include "SaveGameHandler.generated.h"

UCLASS()
class ENDLESSRUNNER_API ASaveGameHandler : public AActor
{
	GENERATED_BODY()

private:
	FString SlotName;
	bool bNewSave;
	
public:	
	// Sets default values for this actor's properties
	ASaveGameHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void FetchSaveGame();

private:
	USaveGameState* SaveGameState;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Save State")
	TSubclassOf<class USaveGameState> SaveGameClass;

public:
	void TrySetNewHighScore(int32 NewHighScore);

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetHighScore() const { return SaveGameState->GetHighScore(); }

};
