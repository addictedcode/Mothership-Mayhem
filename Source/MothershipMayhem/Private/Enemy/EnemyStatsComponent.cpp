// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UEnemyStatsComponent::UEnemyStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (DoTDamage > 0)
	{
		this->timeSinceLastDoTTick += DeltaTime;
		if (this->timeSinceLastDoTTick >= this->DoTTickRate)
		{
			this->timeSinceLastDoTTick = 0;
			this->TakeDamage(DoTDamage);
		}
	}
}

//Take damage and return whether the enemy reached 0 HP or not
bool UEnemyStatsComponent::TakeDamage(int damage)
{
	this->HP -= damage;

	if (this->HP <= 0)
	{
		this->GetOwner()->Destroy();
		this->GetWorld()->GetTimerManager().ClearTimer(DoTTimer);
		
		return true;
	}

	return false;
}

void UEnemyStatsComponent::ApplyDamageOverTime(int damage, float duration)
{
	this->DoTDamage = damage;
	GetWorld()->GetTimerManager().SetTimer(DoTTimer, this, &UEnemyStatsComponent::RemoveDoT, duration, false);
}

void UEnemyStatsComponent::RemoveDoT()
{
	this->DoTDamage = 0;
}

