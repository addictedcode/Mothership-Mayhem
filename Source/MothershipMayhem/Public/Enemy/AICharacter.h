// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable)
		void UpdateWalkSpeed(float newWalkSpeed);

	UFUNCTION(BlueprintCallable)
		void AttackTarget(AActor* target);

	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;
	UPROPERTY(EditAnywhere, Category = Projectile)
		AActor* bulletPool;

	class UEnemyStatsComponent* enemyStats;

	float moveSpeedMultiplier = 1.0f;

	void ChangeSpeedMultiplier(float multiplier);

	bool isStunned = false;

	void SetActorActivation(bool state);

private:
	float timeToReload = 2.0f;
	float currentReloadTime = 0;
};
