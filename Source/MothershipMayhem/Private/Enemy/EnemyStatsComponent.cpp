// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/AICharacter.h"

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
void UEnemyStatsComponent::TakeDamage(int damage)
{
	this->HP -= damage;

	if (this->HP <= 0)
	{
		this->GetOwner()->Destroy();
		this->GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void UEnemyStatsComponent::ApplyDamageOverTime(int damage, float duration)
{
	this->DoTDamage = damage;
	GetWorld()->GetTimerManager().SetTimer(DoTTimer, this, &UEnemyStatsComponent::RemoveDoT, duration, false);
}

void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment)
{
	FTimerDelegate timerDelegate;
	switch (ailment)
	{
	case BURN:
		if (this->currentStatusAilment == FREEZE)
		{
			GetWorld()->GetTimerManager().ClearTimer(DebuffTimer);
			this->ApplyMovespeedMultiplier(1.0f);
		}
		break;
	case WET:
		break;
	case FREEZE:
		if (this->currentStatusAilment != WET) {
			if (this->currentStatusAilment != FREEZE)
				this->ApplyMovespeedMultiplier(0.5f);

			timerDelegate.BindUFunction(this, FName("ApplyMovespeedMultiplier"), 1.0f);

			GetWorld()->GetTimerManager().ClearTimer(DebuffTimer);
			GetWorld()->GetTimerManager().SetTimer(DebuffTimer, timerDelegate, 5.0f, false);
		}
		else
		{
			this->ApplyMovespeedMultiplier(0.0f);

			timerDelegate.BindUFunction(this, FName("ApplyMovespeedMultiplier"), 1.0f);

			GetWorld()->GetTimerManager().ClearTimer(DebuffTimer);
			GetWorld()->GetTimerManager().SetTimer(DebuffTimer, timerDelegate, 5.0f, false);
		}
		break;
	case SHOCKING:
		this->ApplyMovespeedMultiplier(0.0f);

		timerDelegate.BindUFunction(this, FName("ApplyMovespeedMultiplier"), 1.0f);

		GetWorld()->GetTimerManager().ClearTimer(DebuffTimer);
		GetWorld()->GetTimerManager().SetTimer(DebuffTimer, timerDelegate, 2.0f, false);
		break;
	default:
		break;
	}
	this->currentStatusAilment = ailment;
	
}

void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, FVector knockbackStrength)
{
	this->movementComponent->Launch(knockbackStrength);
	this->ApplyStatusEffect(ailment);
}

void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, int damage, float duration)
{
	this->ApplyDamageOverTime(damage, duration);
	this->ApplyStatusEffect(ailment);
}

void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, int directDamage, int DoTdamage, float duration)
{
	this->TakeDamage(directDamage);

	if (!this->GetOwner()->IsPendingKillPending())
	{
		this->ApplyStatusEffect(ailment, DoTdamage, duration);
	}
}

void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, int damage)
{
	switch (ailment)
	{
	case SHOCKING:
		if (this->currentStatusAilment == WET)
			TakeDamage(damage * 2);
		else
			TakeDamage(damage);
		break;
	default:
		TakeDamage(damage);
		break;
	}

	if (!this->GetOwner()->IsPendingKillPending())
		this->ApplyStatusEffect(ailment);
}

void UEnemyStatsComponent::RemoveDoT()
{
	this->DoTDamage = 0;
}

void UEnemyStatsComponent::ApplyMovespeedMultiplier(float multiplier)
{
	AAICharacter* parent = Cast<AAICharacter>(this->GetOwner());
	if (parent != nullptr)
	{
		if (multiplier == 0.0f)
			this->movementComponent->SetComponentTickEnabled(false);
		else {
			this->movementComponent->SetComponentTickEnabled(true);
			parent->ChangeSpeedMultiplier(multiplier);
			if (multiplier == 1.0f)
				this->currentStatusAilment = NONE;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WHY IS ENEMYSTATS NOT ATTACHED TO AN AICHARACTER"));
	}
}

