// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretGun.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API ATurretGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttackTarget(AActor* targetActor);

	void UpdateReloadTime(float newSecPerShot);

	void UpdateProjectileStats(float damage, float speed, bool isBouncing, float gravityScale);

	void SetActorActivation(bool state);

	UFUNCTION(BlueprintCallable)
	void SetLaunchArea(UChildActorComponent* launchArea);

	#pragma region Projectile shooting
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;
	UPROPERTY(EditAnywhere, Category = Projectile)
		AActor* bulletPool;
	UPROPERTY(EditAnywhere, Category = Projectile)
		UChildActorComponent* ProjectileLaunchArea;
	#pragma endregion

private:
	AActor* target;

	float timeToReload;
	float currentReloadTime = 0;

	float attackDamage;
	float projectileSpeed;
	bool hasBouncingAttack;
	float projectileGravityScale;
};
