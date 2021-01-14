// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatsComponent.generated.h"

UENUM()
enum StatusEffects{NONE = 0, BURN = 1, FREEZE = 2, WET = 3, SHOCKING = 4, DISORIENTED = 5, DANCE = 6};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOTHERSHIPMAYHEM_API UEnemyStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyStatsComponent();

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
		class UCharacterMovementComponent* movementComponent;

	void TakeDamage(int damage);

	void ApplyDamageOverTime(int damage, float duration);

	void ApplyStatusEffect(StatusEffects ailment);
	
	void ApplyStatusEffect(StatusEffects ailment, FVector knockbackStrength);

	void ApplyStatusEffect(StatusEffects ailment, int damage, float duration);
	
	void ApplyStatusEffect(StatusEffects ailment, int directDamage, int DoTdamage, float duration);

	void ApplyStatusEffect(StatusEffects ailment, int damage);

	UFUNCTION()
		void ApplyMovespeedMultiplier(float multiplier);

	UFUNCTION()
		void ApplyStun(bool stunned);

	void ResetComponent();

private:
	UPROPERTY(EditAnywhere, Category = "Stats")
		int MaxHP = 10;

	int HP;

	FTimerHandle DoTTimer;
	float const DoTTickRate = 1.0f;
	float timeSinceLastDoTTick = 0;
	int DoTDamage = 0;

	void RemoveDoT();

	StatusEffects currentStatusAilment = NONE;

	FTimerHandle DebuffTimer;

	FTimerHandle StunTimer;
};
