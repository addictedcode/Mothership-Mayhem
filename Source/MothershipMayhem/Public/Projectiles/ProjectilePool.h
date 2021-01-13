// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectilePool.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API AProjectilePool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectilePool();
	
	//request an object from the pool
	class AMMProjectileBase* SpawnObject(UClass* objectClass, FVector loc, FRotator rot, FActorSpawnParameters spawnParams);
	//return an object to the pool
	void ReturnObject(AActor* returnedObject);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	std::vector<AActor*> SpawnedPool;
	std::vector<AActor*> DisabledSpawns;
};