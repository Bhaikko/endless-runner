// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Follower.generated.h"

UCLASS()
class ENDLESSRUNNER_API AFollower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFollower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* FollowerMesh;

private:
	class AEndlessRunnerCharacter* RunnerCharacterReference;

	void MoveTowardsPlayer(float DeltaTime);

	bool bShouldFollow;

	UFUNCTION()
	virtual void Destroy();


public:
	void StopFollowing();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float ChaseSpeed;

};
