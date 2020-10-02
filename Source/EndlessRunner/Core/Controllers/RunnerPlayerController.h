// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunnerPlayerController.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<class UUserWidget> HUDClass;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UUserWidget* HUDClassWidget;

private:
	void SetupHUD();
	
};
