// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include "GameFramework/Actor.h"
#include "EnemyPool.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API AEnemyPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		AActor* bulletPool;

	void SpawnEnemy(TSubclassOf<AActor> ActorToSpawn, FVector loc, FRotator rot, FActorSpawnParameters spawnParams);

private:

	std::map<TSubclassOf<AActor>, std::vector<AActor*>> SpawnedPool;
	std::map<TSubclassOf<AActor>, std::vector<AActor*>> DisabledSpawns;
};
