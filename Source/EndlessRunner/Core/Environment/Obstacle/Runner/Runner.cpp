// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"


ARunner::ARunner() 
{
    bJumping = false;
}

void ARunner::BeginPlay() 
{
    Super::BeginPlay();


    JumpPos = ObstacleMesh->GetComponentLocation();
    JumpPos.Z += 100.0f;

}

void ARunner::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (!PlayerReference) {
        UE_LOG(LogTemp, Warning, TEXT("Player Reference Not Found"));
    }

    float Distance = GetActorLocation().X - PlayerReference->GetActorLocation().X;
    if (Distance <= 500.0f) {
        bJumping = true;

        SetActorLocation(FVector(
            ObstacleMesh->GetComponentLocation().X,
            ObstacleMesh->GetComponentLocation().Y,
            FMath::Lerp<float>(ObstacleMesh->GetComponentLocation().Z, JumpPos.Z, DeltaTime * 10.0f)
        ));
        
    }
}
