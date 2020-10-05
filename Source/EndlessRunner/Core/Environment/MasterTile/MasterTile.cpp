// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "EndlessRunner/EndlessRunnerGameMode.h"
#include "EndlessRunner/Core/Environment/Obstacle/Pipe/Pipe.h"
#include "EndlessRunner/Core/Environment/Obstacle/Box/BoxObstacle.h"
#include "EndlessRunner/Core/Environment/Pickup/Coin/Coin.h"
#include "EndlessRunner/Core/Environment/Pickup/Magnet/Magnet.h"
#include "EndlessRunner/Core/Environment/Pickup/JumpBoots/JumpBoots.h"


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

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollider->SetupAttachment(CubeMesh);
	// BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(CubeMesh);


	// Left Lane
	Lane0 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane0"));
	Lane0->SetupAttachment(CubeMesh);

	// Middle Lane
	Lane1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane1"));
	Lane1->SetupAttachment(CubeMesh);

	// Right lane
	Lane2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Lane2"));
	Lane2->SetupAttachment(CubeMesh);


}

// Called when the game starts or when spawned
void AMasterTile::BeginPlay()
{
	Super::BeginPlay();
	
	// Binding Overlap Delegate for spawning new tiles
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMasterTile::TileSpawnHandler);

	// Spawning Obstacle 
	AEndlessRunnerGameMode* GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode->GetScore() >= 2) {
		SpawnObstacles();	
	}

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
	AEndlessRunnerCharacter* CollidedActor = Cast<AEndlessRunnerCharacter>(OtherActor);
	if (!CollidedActor) {
		return;
	}

	AEndlessRunnerGameMode* GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SpawnTile();

	// Increaing Score
	GameMode->IncreaseScore(1);

	// Increasing Speed of Character
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(CollidedActor->GetMovementComponent());
	if (CharacterMovementComponent) {
		CharacterMovementComponent->MaxWalkSpeed = FMath::Clamp<float>(
			CharacterMovementComponent->MaxWalkSpeed * 2.01,
			600.0f,
			1200.0f
		);
	}

	// Binding Destroy Delegate
	// THE DESTROY DELAY WILL BE BASED ON GAME SPEED LATER
	GetWorld()->GetTimerManager().SetTimer(DestroyTileHandle, this, &AMasterTile::HandleDestruction, 5.0f);

}

void AMasterTile::HandleDestruction() 
{
	Destroy();
}

void AMasterTile::SpawnObstacles() 
{
	SpawnObstacleInLane(Lane0);
	SpawnObstacleInLane(Lane1);
	SpawnObstacleInLane(Lane2);
}

void AMasterTile::SpawnObstacleInLane(UArrowComponent* Lane) 
{
	if (!PipeClass || !BoxClass || !CoinClass || !MagnetClass || !JumpBootClass) {
		UE_LOG(LogTemp, Warning, TEXT("One of Obstacle or Pickup Class Missing."));
		return;
	}

	if (!Lane) {
		UE_LOG(LogTemp, Warning, TEXT("no Lane Found, Intresting"));
		return;
	}

	// Randomly Spawning Obstacle using Random Int 
	float ChanceOfSpawning = FMath::RandRange(0.0f, 1.0f);

	if (ChanceOfSpawning >= 0.0f && ChanceOfSpawning <= 0.4f) {
		APipe* SpawnedPipe = GetWorld()->SpawnActor<APipe>(
			PipeClass,
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.4f && ChanceOfSpawning <= 0.5f) {
		ABoxObstacle* SpawnedBox = GetWorld()->SpawnActor<ABoxObstacle>(
			BoxClass,
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.5f && ChanceOfSpawning <= 0.9f) {
		ACoin* SpawnedCoin = GetWorld()->SpawnActor<ACoin>(
			CoinClass,
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.9f && ChanceOfSpawning <= 0.95f) {
		AMagnet* SpawnedMagnet = GetWorld()->SpawnActor<AMagnet>(
			MagnetClass,
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	} else if (ChanceOfSpawning > 0.95f && ChanceOfSpawning <= 1.00f) {
		AJumpBoots* SpawnedMagnet = GetWorld()->SpawnActor<AJumpBoots>(
			JumpBootClass,
			Lane->GetComponentLocation(),
			Lane->GetComponentRotation()
		);
	}
}

UArrowComponent* AMasterTile::GetSpawnPoint() const
{
	return this->SpawnPoint;
}

