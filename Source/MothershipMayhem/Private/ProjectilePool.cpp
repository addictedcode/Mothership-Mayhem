// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"
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
	if (this->DisabledSpawns.empty()) {
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(objectClass, loc, rot, spawnParams);
		this->SpawnedPool.push_back(SpawnedActorRef);
		AMMProjectileBase* projectile = Cast<AMMProjectileBase>(SpawnedActorRef);
		if (projectile != nullptr)
		{
			projectile->parentPool = this;
		}
		
		return projectile;
	}
	else
	{
		AActor* ReusedActorRef = this->DisabledSpawns.back();
		this->DisabledSpawns.pop_back();

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

		this->SpawnedPool.push_back(ReusedActorRef);

		return Cast<AMMProjectileBase>(ReusedActorRef);
	}
}

void AProjectilePool::ReturnObject(AActor* returnedObject)
{
	DisabledSpawns.push_back(returnedObject);
	SpawnedPool.erase(std::find(SpawnedPool.begin(), SpawnedPool.end(), returnedObject));
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

