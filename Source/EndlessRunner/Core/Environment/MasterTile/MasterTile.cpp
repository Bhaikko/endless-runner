// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "EndlessRunner/EndlessRunnerGameMode.h"

// Sets default values
AMasterTile::AMasterTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Considering X-axis as forward direction to spawn tiles

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	CubeMesh->SetupAttachment(Root);
	CubeMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	CubeMesh->SetRelativeScale3D(FVector(10.0f, 10.0f, 0.1f));

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(CubeMesh);
	SpawnPoint->SetRelativeLocation(FVector(0.0f, -50.0f, 0.0f));

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollider->SetupAttachment(SpawnPoint);
	// BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AMasterTile::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMasterTile::TileSpawnHandler);
}

// Called every frame
void AMasterTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterTile::TileSpawnHandler(
	UPrimitiveComponent* OverlappedComponent,
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
) {
	UE_LOG(LogTemp, Warning, TEXT("Player Collided"));
	AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

	AEndlessRunnerGameMode* GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SpawnTile();

}

UArrowComponent* AMasterTile::GetSpawnPoint() const
{
	return this->SpawnPoint;
}

