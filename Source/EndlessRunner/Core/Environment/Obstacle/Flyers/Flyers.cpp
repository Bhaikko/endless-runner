// Fill out your copyright notice in the Description page of Project Settings.


#include "Flyers.h"

#include "GameFramework/CharacterMovementComponent.h"

void AFlyers::BeginPlay() 
{
    Super::BeginPlay();

    MovementComponent = Cast<UCharacterMovementComponent>(GetComponentByClass(UCharacterMovementComponent::StaticClass()));

    MovementComponent->GravityScale = 0.0f;
    DropSpeed = 1000.0f;
}


void AFlyers::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);


    float Distance = GetActorLocation().Z - PlayerReference->GetActorLocation().Z;

    if (Distance > 100.0f) {
        MoveDown(DeltaTime);
    }

}

void AFlyers::MoveDown(float DeltaTime) 
{
    SetActorLocation(FVector(
        GetActorLocation().X,
        GetActorLocation().Y,
        GetActorLocation().Z - (DropSpeed * DeltaTime)
    ));
}
