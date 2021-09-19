// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawner.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyPool.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = root;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->TimeSinceLastSpawn += DeltaTime;
	this->currentTime += DeltaTime;
	if (this->TimeSinceLastSpawn >= this->SpawnCooldown &&
		this->EnemiesToSpawn > this->EnemiesSpawned)
	{
		this->TimeSinceLastSpawn = 0.0f;
		SpawnEnemy();
		this->EnemiesSpawned++;
	}
}

void AEnemySpawner::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (enemyPool != nullptr)
		enemyPool->SpawnEnemy(this->ActorToSpawn, this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
	else
		UE_LOG(LogTemp, Error, TEXT("NO ENEMYPOOL"));
}

