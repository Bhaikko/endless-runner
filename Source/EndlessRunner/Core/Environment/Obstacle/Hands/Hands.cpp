// Fill out your copyright notice in the Description page of Project Settings.


#include "Hands.h"
#include "Components/SkeletalMeshComponent.h"

AHands::AHands() 
{
    HandsMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh1"));
	HandsMesh1->SetupAttachment(Root);

    HandsMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh2"));
	HandsMesh2->SetupAttachment(Root);

    HandsMesh3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh3"));
	HandsMesh3->SetupAttachment(Root);
    
    HandsMesh4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh4"));
	HandsMesh4->SetupAttachment(Root);

    HandsMesh5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh5"));
	HandsMesh5->SetupAttachment(Root);
}

void AHands::BeginPlay() 
{
    Super::BeginPlay();
}
