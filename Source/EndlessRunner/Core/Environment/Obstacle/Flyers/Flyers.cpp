// Fill out your copyright notice in the Description page of Project Settings.


#include "Flyers.h"


void AFlyers::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    MoveDown();

}

void AFlyers::MoveDown() 
{
    AddMovementInput(FVector(0.0f, 0.0f, -1.0f), 1.0f, true);
}
