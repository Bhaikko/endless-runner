// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndlessRunner/Core/Resources/Enums.h"
#include "LaneHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER_API ULaneHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULaneHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<FVector> Lanes;
	int32 CurrentLaneY, CurrentLaneZ;
	int32 NewLaneY, NewLaneZ;
	bool bShouldSwitch;

	class AEndlessRunnerGameMode* GameModeReference;
	class AEndlessRunnerCharacter* RunnerCharacterReference;

private:
	void LerpBetweenLanes(float DeltaTime);

public:
	void UpdateLanes();

	void ChangeLane(EndlessRunnerEnums::EMovementDirection Direction);

private:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character Attributes")
	float ChangeLaneSpeed;
		
};
