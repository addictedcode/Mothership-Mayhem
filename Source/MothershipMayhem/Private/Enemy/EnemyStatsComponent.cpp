// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyController.h"

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
	this->HP = this->MaxHP;
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
			this->timeSinceLastDoTTick -= this->DoTTickRate;
			this->TakeDamage(DoTDamage);
		}
	}
}

//Take x damage
void UEnemyStatsComponent::TakeDamage(int damage)
{
	this->HP -= damage;

	if (this->HP <= 0)
	{
		AAICharacter* parent = Cast<AAICharacter>(this->GetOwner());
		if (parent != nullptr)
		{
			parent->SetActorActivation(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("WHY IS ENEMYSTATS NOT ATTACHED TO AN AICHARACTER"));
		}
		this->GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}
//Starts the flag for taking damage over time
void UEnemyStatsComponent::ApplyDamageOverTime(int damage, float duration)
{
	this->DoTDamage = damage;
	GetWorld()->GetTimerManager().SetTimer(DoTTimer, this, &UEnemyStatsComponent::RemoveDoT, duration, false);
}
//Function for just applying a status effect
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
		if (this->currentStatusAilment == BURN)
		{
			this->GetWorld()->GetTimerManager().ClearTimer(DoTTimer);
			this->RemoveDoT();
		}
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
		this->ApplyStun(true);

		timerDelegate.BindUFunction(this, FName("ApplyMovespeedMultiplier"), 1.0f);

		GetWorld()->GetTimerManager().ClearTimer(DebuffTimer);
		GetWorld()->GetTimerManager().SetTimer(DebuffTimer, timerDelegate, 2.0f, false);

		timerDelegate.Unbind();
		timerDelegate.BindUFunction(this, FName("ApplyStun"), false);
		
		GetWorld()->GetTimerManager().ClearTimer(StunTimer);
		GetWorld()->GetTimerManager().SetTimer(StunTimer, timerDelegate, 2.0f, false);
		break;
	case DISORIENTED:
		Cast<AEnemyController>(Cast<AAICharacter>(this->GetOwner())->Controller)->OnCharacterDisoriented(10.0f);
		break;
	case DANCE:
		this->ApplyMovespeedMultiplier(0.0f);
		this->ApplyStun(true);

		timerDelegate.BindUFunction(this, FName("ApplyMovespeedMultiplier"), 1.0f);

		GetWorld()->GetTimerManager().ClearTimer(DebuffTimer);
		GetWorld()->GetTimerManager().SetTimer(DebuffTimer, timerDelegate, 2.0f, false);

		timerDelegate.Unbind();
		timerDelegate.BindUFunction(this, FName("ApplyStun"), false);

		GetWorld()->GetTimerManager().ClearTimer(StunTimer);
		GetWorld()->GetTimerManager().SetTimer(StunTimer, timerDelegate, 2.0f, false);
		break;
	default:
		break;
	}
	this->currentStatusAilment = ailment;
	
}
//Function for applying a status effect with a knockback
void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, FVector knockbackStrength)
{
	this->movementComponent->Launch(knockbackStrength);
	this->ApplyStatusEffect(ailment);
}
//Function for inflicting a damage over time status effect
void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, int damage, float duration)
{
	this->ApplyDamageOverTime(damage, duration);
	this->ApplyStatusEffect(ailment);
}
//Function for inflicting a damage over time status effect that also does direct damage
void UEnemyStatsComponent::ApplyStatusEffect(StatusEffects ailment, int directDamage, int DoTdamage, float duration)
{
	this->TakeDamage(directDamage);

	if (!this->GetOwner()->IsHidden())
	{
		this->ApplyStatusEffect(ailment, DoTdamage, duration);
	}
}
//Function for applying a status effect with direct damage
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

	if (!this->GetOwner()->IsHidden())
		this->ApplyStatusEffect(ailment);
}

void UEnemyStatsComponent::RemoveDoT()
{
	this->DoTDamage = 0;
	this->currentStatusAilment = NONE;
}
//Changes the movespeed multiplier in AICharacter while disabling the movement component tick function if the multiplier is 0 (rooted or stunned)
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
//Sets the AICharacter isStunned bool
void UEnemyStatsComponent::ApplyStun(bool stunned)
{
	AAICharacter* parent = Cast<AAICharacter>(this->GetOwner());
	if (parent != nullptr)
	{
		parent->isStunned = stunned;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WHY IS ENEMYSTATS NOT ATTACHED TO AN AICHARACTER"));
	}
}
//Reinitializes the variables in the component when reused in object pooling
void UEnemyStatsComponent::ResetComponent()
{
	this->HP = this->MaxHP;
	this->timeSinceLastDoTTick = 0;
	this->DoTDamage = 0;
	this->ApplyMovespeedMultiplier(1.0f);
}

