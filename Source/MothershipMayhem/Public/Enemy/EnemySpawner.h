// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOTHERSHIPMAYHEM_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		class AEnemyPool* enemyPool;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		int EnemiesToSpawn = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int EnemiesSpawned = 0;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		float SpawnCooldown = 10.0f;
	float TimeSinceLastSpawn = 0.0f;
	float currentTime = 0.0f;

	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();
};
