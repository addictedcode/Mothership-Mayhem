// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SpawnerComponent.h"
#include "Enemy/AICharacter.h"

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
			FVector loc = this->SpawnPoint->GetActorLocation();
			FRotator rot = this->SpawnPoint->GetActorRotation();

			SpawnObject(loc, rot);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No reference to actor"));
		}
	}

	for (int i = 0; i < SpawnedPool.size(); i++)
	{
		if (SpawnedPool[i]->IsHidden())
		{
			DisabledSpawns.push_back(SpawnedPool[i]);
			SpawnedPool.erase(SpawnedPool.begin() + i);
			i--;
			UE_LOG(LogTemp, Display, TEXT("Despawning"));
		}
	}
}

void USpawnerComponent::SpawnObject(FVector loc, FRotator rot)
{
	if (this->DisabledSpawns.empty()) {
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, loc, rot, SpawnParams);
		AAICharacter* spawnedEnemy = Cast<AAICharacter>(SpawnedActorRef);
		if (spawnedEnemy != nullptr)
		{
			spawnedEnemy->bulletPool = this->bulletPool;
		}
		this->SpawnedPool.push_back(SpawnedActorRef);
	}
	else
	{
		AActor* ReusedActorRef = this->DisabledSpawns.back();
		this->DisabledSpawns.pop_back();

		ReusedActorRef->SetActorLocation(loc);

		AAICharacter* spawnedEnemy = Cast<AAICharacter>(ReusedActorRef);
		//Unhide the actor when reused
		if (spawnedEnemy != nullptr)
		{
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawn is not an enemy"));
		}

		this->SpawnedPool.push_back(ReusedActorRef);
	}
}
