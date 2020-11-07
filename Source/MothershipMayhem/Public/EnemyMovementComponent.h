// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMovementComponent.generated.h"


UCLASS(transient, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOTHERSHIPMAYHEM_API UEnemyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "pawnvariables") APawn* ControlledPawn;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReactivateActor();

private:
	float SpawnCooldown = 5.0f;
	float TimeSinceLastSpawn = 0.0f;
};
