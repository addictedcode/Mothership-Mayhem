// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatsComponent.generated.h"

UENUM()
enum class StatusEffects : uint8
{NONE = 0, BURN = 1, FREEZE = 2, WET = 3, SHOCKING = 4, DISORIENTED = 5, DANCE = 6};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

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

	UFUNCTION(BlueprintCallable)
		void TakeDamage(int damage);

	void ApplyDamageOverTime(int damage, float duration);
	
	#pragma region ApplyStatusEffect Function overloads
	UFUNCTION(BlueprintCallable)
		void ApplyStatusEffect(StatusEffects ailment);
	void ApplyStatusEffect(StatusEffects ailment, FVector knockbackStrength);
	void ApplyStatusEffect(StatusEffects ailment, int damage, float duration);
	void ApplyStatusEffect(StatusEffects ailment, int directDamage, int DoTdamage, float duration);
	void ApplyStatusEffect(StatusEffects ailment, int damage);
	#pragma endregion
	
	UFUNCTION()
		void ApplyMovespeedMultiplier(float multiplier);

	UFUNCTION()
		void ApplyStun(bool stunned);

	void ResetComponent();

	// this is an event called when the Enemy dies;
	UPROPERTY(BlueprintAssignable)
		FOnDeathDelegate OnDeath;

	void SetMaxHP(int newHP);
	int getCurrentHP();

private:
	UPROPERTY(EditAnywhere, Category = "Stats")
		int MaxHP = 10;

	int HP;

	float const DoTTickRate = 1.0f;
	float timeSinceLastDoTTick = 0;
	int DoTDamage = 0;

	void RemoveDoT();

	StatusEffects currentStatusAilment = StatusEffects::NONE;
	
	#pragma region FTimerHandles
	FTimerHandle DoTTimer;
	FTimerHandle DebuffTimer;
	FTimerHandle StunTimer;
	#pragma endregion 
};
