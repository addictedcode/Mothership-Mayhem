// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPool.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyController.h"

// Sets default values
AEnemyPool::AEnemyPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (std::map<TSubclassOf<AActor>, std::vector<AActor*>>::iterator iter = SpawnedPool.begin(); iter != SpawnedPool.end(); iter++) {
		for (int i = 0; i < iter->second.size(); i++)
		{
			if (iter->second[i]->IsHidden())
			{
				if (DisabledSpawns.count(iter->first))
					DisabledSpawns[iter->first].push_back(iter->second[i]);
				else
				{
					std::vector<AActor*> newEntry;
					newEntry.push_back(iter->second[i]);
					DisabledSpawns.insert(std::pair<TSubclassOf<AActor>, std::vector<AActor*>>(iter->first, newEntry));
				}
				
				iter->second.erase(iter->second.begin() + i);
				i--;
				UE_LOG(LogTemp, Display, TEXT("Despawning"));
			}
		}
	}
}

void AEnemyPool::SpawnEnemy(TSubclassOf<AActor> ActorToSpawn, FVector loc, FRotator rot, FActorSpawnParameters spawnParams)
{
	if (!DisabledSpawns.count(ActorToSpawn) || DisabledSpawns[ActorToSpawn].empty()) 
	{
		if (ActorToSpawn != NULL) {
			AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, loc, rot, spawnParams);
			AAICharacter* spawnedEnemy = Cast<AAICharacter>(SpawnedActorRef);
			if (spawnedEnemy != nullptr)
			{
				spawnedEnemy->bulletPool = this->bulletPool;
			}
			if (SpawnedPool.count(ActorToSpawn))
				SpawnedPool[ActorToSpawn].push_back(SpawnedActorRef);
			else {
				std::vector<AActor*> newEntry;
				newEntry.push_back(SpawnedActorRef);
				SpawnedPool.insert(std::pair<TSubclassOf<AActor>, std::vector<AActor*>>(ActorToSpawn, newEntry));
			}
		}
	}
	else
	{
		AActor* ReusedActorRef = DisabledSpawns[ActorToSpawn].back();
		DisabledSpawns[ActorToSpawn].pop_back();

		ReusedActorRef->SetActorLocation(loc);

		AAICharacter* spawnedEnemy = Cast<AAICharacter>(ReusedActorRef);
		//Unhide the actor when reused
		if (spawnedEnemy != nullptr)
		{
			spawnedEnemy->SetActorActivation(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawn is not an enemy"));
		}

		SpawnedPool[ActorToSpawn].push_back(ReusedActorRef);
	}
}

void AEnemyPool::UpdateEnemyTargets(AActor* newTarget) {
	std::map<TSubclassOf<AActor>, std::vector<AActor*>>::iterator iter;

	for (iter = SpawnedPool.begin(); iter != SpawnedPool.end(); iter++)
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			AAICharacter* currentEnemy = Cast<AAICharacter>(iter->second[i]);
			AEnemyController* currentController = Cast<AEnemyController>(currentEnemy->GetController());
			if (currentController) {
				currentController->SetNewTarget(newTarget);
			}
		}
	}
}