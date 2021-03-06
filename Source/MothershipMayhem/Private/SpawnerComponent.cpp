// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerComponent.h"
#include "EnemyMovementComponent.h"

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
		this->SpawnedPool.push_back(SpawnedActorRef);
		UE_LOG(LogTemp, Display, TEXT("SPAWNING"));
	}
	else
	{
		AActor* ReusedActorRef = this->DisabledSpawns.back();
		this->DisabledSpawns.pop_back();

		ReusedActorRef->SetActorLocation(loc);

		UEnemyMovementComponent* MovementComponent = ReusedActorRef->FindComponentByClass<UEnemyMovementComponent>();
		if (MovementComponent != nullptr)
		{
			MovementComponent->ReactivateActor();
			//MovementComponent->GetOwner()->SetActorHiddenInGame(false);
			UE_LOG(LogTemp, Warning, TEXT("REVEALING"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NO MOVEMENT COMPONENT ATTACHED"));
		}

		UE_LOG(LogTemp, Display, TEXT("RESPAWNING"));

		this->SpawnedPool.push_back(ReusedActorRef);
	}
}
