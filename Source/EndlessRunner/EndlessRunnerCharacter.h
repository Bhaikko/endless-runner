// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EndlessRunnerCharacter.generated.h"

UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	
public:
	AEndlessRunnerCharacter();

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void MoveLeft();
	void MoveRight();
	void MoveDown();

	virtual void Jump() override;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character Attributes")
	float ChangeLaneSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attributes")
	float SlideDuration;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool IsMagnetActive() const { return bMagnetActive; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsSliding() const { return bSlide; }

private:
	int32 Lane;	// Index for current lane, the character is, 0 -> Left, 1 -> Middle, 2 -> Right
	int32 NewLane;
	float LaneY[3];
	bool bShouldSwitch;

	bool bSlide;

	// Pickup Statistics
	bool bMagnetActive;

private:
	void LerpBetweenLanes(float DeltaTime);

	UFUNCTION()
	void CancelSlide();

public:
	void HandleDeath();
	void SetMagnetStatus(bool bStatus);

};

