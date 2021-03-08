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
	
	#pragma region BehaviorTree variables and functions
	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable)
		void UpdateWalkSpeed(float newWalkSpeed);

	UFUNCTION(BlueprintCallable)
		void AttackTarget(AActor* target);
	#pragma endregion

	#pragma region Projectile shooting
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;
	UPROPERTY(EditAnywhere, Category = Projectile)
		AActor* bulletPool;
	#pragma endregion
	
	class UEnemyStatsComponent* enemyStats;

	void ChangeSpeedMultiplier(float multiplier);

	void UpdateReloadTime(float newSecPerShot);

	void UpdateProjectileStats(float damage, float speed, bool isBouncing, float gravityScale);

	bool isStunned = false;

	void SetActorActivation(bool state);

	UFUNCTION(BlueprintImplementableEvent)
		void DeathGang();

private:
	float moveSpeedMultiplier = 1.0f;
	float timeToReload = 2.0f;
	float currentReloadTime = 0;

	float attackDamage;
	float projectileSpeed;
	bool hasBouncingAttack;
	float projectileGravityScale;
};
