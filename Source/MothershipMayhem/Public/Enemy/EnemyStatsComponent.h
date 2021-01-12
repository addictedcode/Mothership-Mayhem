// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatsComponent.generated.h"


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

	UFUNCTION(BlueprintCallable, Category = "Stats")
		bool TakeDamage(int damage);

	UFUNCTION(BlueprintCallable, Category = "Stats")
		void ApplyDamageOverTime(int damage, float duration);

private:
	UPROPERTY(EditAnywhere, Category = "Stats")
		int HP = 10;

	FTimerHandle DoTTimer;
	float DoTTickRate = 1.0f;
	float timeSinceLastDoTTick = 0;
	int DoTDamage = 0;

	void RemoveDoT();
};
