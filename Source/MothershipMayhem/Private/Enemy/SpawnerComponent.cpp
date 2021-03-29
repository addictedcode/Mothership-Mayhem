// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SpawnerComponent.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyPool.h"

// Sets default values for this component's properties
USpawnerComponent::USpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SpawnPoint = GetOwner();
	// ...
	
}


// Called every frame
void USpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	this->TimeSinceLastSpawn += DeltaTime;
	this->currentTime += DeltaTime;
	if (this->TimeSinceLastSpawn >= this->SpawnCooldown)
	{
		if (this->SpawnPoint != nullptr) {
			this->TimeSinceLastSpawn = 0.0f;
			SpawnEnemy();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No reference to actor"));
		}
	}
}

void USpawnerComponent::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (enemyPool != nullptr)
		enemyPool->SpawnEnemy(this->ActorToSpawn, this->SpawnPoint->GetActorLocation(), this->SpawnPoint->GetActorRotation(), SpawnParams);
	else
		UE_LOG(LogTemp, Error, TEXT("NO ENEMYPOOL"));
}


