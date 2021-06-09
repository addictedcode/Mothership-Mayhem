// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ProjectilePool.h"
#include "Character/MMCharacterBase.h"
#include "Projectiles/MMProjectileBase.h" 

// Sets default values
AProjectilePool::AProjectilePool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMMProjectileBase* AProjectilePool::SpawnObject(UClass* objectClass, FVector loc, FRotator rot, FActorSpawnParameters spawnParams)
{
	if (this->DisabledSpawns.find(objectClass) == this->DisabledSpawns.end() || this->DisabledSpawns[objectClass].empty()) {
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(objectClass, loc, rot, spawnParams);
		
		if (this->SpawnedPool.find(objectClass) == this->SpawnedPool.end()) {
			std::vector<AActor*> newList;
			this->SpawnedPool.insert(std::pair<UClass*, std::vector<AActor*>>(objectClass, newList));
		}
		
		this->SpawnedPool[objectClass].push_back(SpawnedActorRef);
		AMMProjectileBase* projectile = Cast<AMMProjectileBase>(SpawnedActorRef);
		if (projectile != nullptr)
		{
			projectile->parentPool = this;
			projectile->SetActorActivation(true);
		}
		
		return projectile;
	}
	else
	{
		AActor* ReusedActorRef = this->DisabledSpawns[objectClass].back();
		this->DisabledSpawns[objectClass].pop_back();

		ReusedActorRef->SetActorLocation(loc);
		ReusedActorRef->SetActorRotation(rot);

		AMMProjectileBase* projectileClass = Cast<AMMProjectileBase>(ReusedActorRef);
		if (projectileClass != nullptr)
		{
			projectileClass->SetActorActivation(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor is not a projectile"));
		}

		this->SpawnedPool[objectClass].push_back(ReusedActorRef);

		return Cast<AMMProjectileBase>(ReusedActorRef);
	}
}

AMMProjectileBase* AProjectilePool::SpawnObjectWDefaultSpawnParams(UClass* objectClass, FVector loc, FRotator rot)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (this->DisabledSpawns.find(objectClass) == this->DisabledSpawns.end() || this->DisabledSpawns[objectClass].empty()) {
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(objectClass, loc, rot, ActorSpawnParams);

		if (this->SpawnedPool.find(objectClass) == this->SpawnedPool.end()) {
			std::vector<AActor*> newList;
			this->SpawnedPool.insert(std::pair<UClass*, std::vector<AActor*>>(objectClass, newList));
		}

		this->SpawnedPool[objectClass].push_back(SpawnedActorRef);
		AMMProjectileBase* projectile = Cast<AMMProjectileBase>(SpawnedActorRef);
		if (projectile != nullptr)
		{
			projectile->parentPool = this;
			projectile->SetActorActivation(true);
			projectile->faction = owningFaction::Player;
		}

		return projectile;
	}
	else
	{
		AActor* ReusedActorRef = this->DisabledSpawns[objectClass].back();
		this->DisabledSpawns[objectClass].pop_back();

		ReusedActorRef->SetActorLocation(loc);
		ReusedActorRef->SetActorRotation(rot);

		AMMProjectileBase* projectileClass = Cast<AMMProjectileBase>(ReusedActorRef);
		if (projectileClass != nullptr)
		{
			projectileClass->SetActorActivation(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor is not a projectile"));
		}

		this->SpawnedPool[objectClass].push_back(ReusedActorRef);

		return Cast<AMMProjectileBase>(ReusedActorRef);
	}
}

void AProjectilePool::ReturnObject(AActor* returnedObject)
{
	if (this->DisabledSpawns.find(returnedObject->GetClass()) == this->DisabledSpawns.end()) {
		std::vector<AActor*> newList;
		this->DisabledSpawns.insert(std::pair<UClass*, std::vector<AActor*>>(returnedObject->GetClass(), newList));
	}
	this->DisabledSpawns[returnedObject->GetClass()].push_back(returnedObject);
	this->SpawnedPool[returnedObject->GetClass()].erase(std::find(
		this->SpawnedPool[returnedObject->GetClass()].begin(), this->SpawnedPool[returnedObject->GetClass()].end(), returnedObject));
}

// Called when the game starts or when spawned
void AProjectilePool::BeginPlay()
{
	Super::BeginPlay();

	AMMCharacterBase* player = Cast<AMMCharacterBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player != nullptr)
	{
		player->bulletPool = this;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found"));
	}
}

// Called every frame
void AProjectilePool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

