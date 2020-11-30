// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EndlessRunner/Core/Resources/Enums.h"
#include "EndlessRunnerCharacter.generated.h"


UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Handlers", meta = (AllowPrivateAccess = "true"))
	class ULaneHandler* LaneHandler;

	
public:
	AEndlessRunnerCharacter();

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void MoveUp();

public:
	virtual void Jump() override;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:
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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsWallRunning() const { return bWallRunning; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsDead() const { return bDead; }

	void UpdateTiles();

private:
	bool bSlide;
	bool bWallRunning;
	bool bDead;

	// Pickup Statistics
	bool bMagnetActive;

private:

	UFUNCTION()
	void CancelSlide();

public:
	void HandleDeath();
	void SetMagnetStatus(bool bStatus);
	void SetWallRunning(bool bStatus);

};

