// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerPlayerController.h"

#include "Blueprint/UserWidget.h"

void ARunnerPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    SetupHUD();
}

void ARunnerPlayerController::SetupHUD() 
{
    if (!HUDClass) {
		UE_LOG(LogTemp, Warning, TEXT("No HUD class assigned."));
		return;
	}

	HUDClassWidget = CreateWidget(this, HUDClass);
	HUDClassWidget->AddToViewport();
}
