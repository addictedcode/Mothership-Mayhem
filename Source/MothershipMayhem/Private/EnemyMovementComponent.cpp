// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"

// Sets default values for this component's properties
UEnemyMovementComponent::UEnemyMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (this->ControlledPawn != nullptr) {
		FVector loc = this->ControlledPawn->GetActorLocation();
		loc.Y += 50 * DeltaTime;
		this->ControlledPawn->SetActorLocation(loc);

		this->TimeSinceLastSpawn += DeltaTime;
		if (this->TimeSinceLastSpawn >= this->SpawnCooldown)
		{
			//this->ControlledPawn->Destroy();
			this->ControlledPawn->SetActorHiddenInGame(true);
			this->ControlledPawn->SetActorEnableCollision(false);
			this->ControlledPawn->SetActorTickEnabled(false);
			this->SetComponentTickEnabled(true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No reference to actor"));
	}
}

void UEnemyMovementComponent::ReactivateActor()
{
	if (this->ControlledPawn != nullptr) {
		this->ControlledPawn->SetActorHiddenInGame(false);
		this->ControlledPawn->SetActorEnableCollision(true);
		this->ControlledPawn->SetActorTickEnabled(true);
		this->SetComponentTickEnabled(true);
		this->TimeSinceLastSpawn = 0;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No reference to actor"));
	}
}
