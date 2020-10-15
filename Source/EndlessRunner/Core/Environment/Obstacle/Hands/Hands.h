// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunner/Core/Environment/Obstacle/Obstacle.h"
#include "Hands.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AHands : public AObstacle
{
	GENERATED_BODY()
	
public:
	AHands();

protected: 
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* HandsMesh1;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* HandsMesh2;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* HandsMesh3;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* HandsMesh4;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* HandsMesh5;

};
