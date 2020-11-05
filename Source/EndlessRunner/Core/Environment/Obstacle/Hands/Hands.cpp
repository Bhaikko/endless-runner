// Fill out your copyright notice in the Description page of Project Settings.


#include "Hands.h"
#include "Components/SkeletalMeshComponent.h"

AHands::AHands() 
{
    HandsMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh1"));
	HandsMesh1->SetupAttachment(RootComponent);

    HandsMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh2"));
	HandsMesh2->SetupAttachment(RootComponent);

    HandsMesh3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh3"));
	HandsMesh3->SetupAttachment(RootComponent);
    
    HandsMesh4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh4"));
	HandsMesh4->SetupAttachment(RootComponent);

    HandsMesh5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh5"));
	HandsMesh5->SetupAttachment(RootComponent);
}

void AHands::BeginPlay() 
{
    Super::BeginPlay();
}
