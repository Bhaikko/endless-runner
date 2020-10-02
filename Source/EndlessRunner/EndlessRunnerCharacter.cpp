// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AEndlessRunnerCharacter

AEndlessRunnerCharacter::AEndlessRunnerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	
	Lane = 1;
	NewLane = 0;

	// These are hard coded, later will be fixed using References from current tile
	LaneY[0] = -330.0f;
	LaneY[1] =   20.0f;
	LaneY[2] =  370.0f;

	ChangeLaneSpeed = 100.0f;
	bShouldSwitch = false;

}

void AEndlessRunnerCharacter::BeginPlay() 
{
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////
// Input
void AEndlessRunnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// PlayerInputComponent->BindAxis("MoveForward", this, &AEndlessRunnerCharacter::MoveForward);
	// PlayerInputComponent->BindAxis("MoveRight", this, &AEndlessRunnerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &AEndlessRunnerCharacter::MoveLeft);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &AEndlessRunnerCharacter::MoveRight);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AEndlessRunnerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AEndlessRunnerCharacter::TouchStopped);

}

void AEndlessRunnerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AEndlessRunnerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AEndlessRunnerCharacter::MoveLeft() 
{
	NewLane = FMath::Clamp<float>(
		Lane - 1,
		0,
		2
	);
	
	bShouldSwitch = true;
	Lane = NewLane;
}

void AEndlessRunnerCharacter::MoveRight() 
{
	NewLane = FMath::Clamp<float>(
		Lane + 1,
		0,
		2
	);

	bShouldSwitch = true;
	Lane = NewLane;
}

void AEndlessRunnerCharacter::LerpBetweenLanes(float DeltaTime) 
{
	FVector CurrentLocation = GetActorLocation();
	float NewLocationY = LaneY[NewLane];
	
	SetActorLocation(FVector(
		CurrentLocation.X,
		FMath::FInterpConstantTo(CurrentLocation.Y, NewLocationY, DeltaTime, ChangeLaneSpeed),
		CurrentLocation.Z
	));


	if (FMath::Abs((NewLocationY - CurrentLocation.Y)) <= 0.01f) {
		bShouldSwitch = false;
	} 
}

void AEndlessRunnerCharacter::Tick(float DeltaTime) 
{
	MoveForward(1.0f);

	if (bShouldSwitch) {
		LerpBetweenLanes(DeltaTime);

	}
}

void AEndlessRunnerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEndlessRunnerCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

