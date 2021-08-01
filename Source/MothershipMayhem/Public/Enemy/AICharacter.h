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
	UPROPERTY(EditAnywhere, Category = Projectile)
		UChildActorComponent* ProjectileLaunchArea;
	#pragma endregion
	
	class UEnemyStatsComponent* enemyStats;

	UFUNCTION(BlueprintCallable)
		UEnemyStatsComponent* getEnemyStats();

	void ChangeSpeedMultiplier(float multiplier);

	void UpdateReloadTime(float newSecPerShot);

	void UpdateProjectileStats(float damage, float speed, bool isBouncing, float gravityScale);

	bool isStunned = false;

	void SetActorActivation(bool state);

	void SuckIntoVacuum(AActor* playerPtr, int executeThreshold);

	UFUNCTION(BlueprintImplementableEvent)
		void DeathGang();

protected:
	float moveSpeedMultiplier = 1.0f;
	float timeToReload;
	float currentReloadTime = 0;

	float attackDamage;
	float projectileSpeed;
	bool hasBouncingAttack;
	float projectileGravityScale;

	AActor* player;
	bool isBeingSucked = false;
};
