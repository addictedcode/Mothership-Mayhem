// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOTHERSHIPMAYHEM_API USpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnerComponent();

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		class AEnemyPool* enemyPool;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* SpawnPoint;

	float SpawnCooldown = 10.0f;
	float TimeSinceLastSpawn = 0.0f;
	float currentTime = 0.0f;

	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();
};
