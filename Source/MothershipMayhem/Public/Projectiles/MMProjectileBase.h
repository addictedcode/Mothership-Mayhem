// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MMProjectileBase.generated.h"

UENUM(BlueprintType)
enum class owningFaction : uint8
{
	Player UMETA(DisplayName="Player"),
	Enemy UMETA(DisplayName="Enemy"),
	Neutral UMETA(DisplayName="Neutral")
};

UCLASS()
class MOTHERSHIPMAYHEM_API AMMProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* collisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* projectileMovement;

	//Projectile lifespan
	float lifespan = 0;
	FTimerHandle projectileLifespanTimerHandle;
	//float currentLifePeriod = 0;

	//Projectile Stats
	UPROPERTY(BlueprintReadOnly)
		float damage = 0;
	UPROPERTY(EditAnywhere)
		bool isPiercing = false;
	float projectileSpeed = 3000.0f;
public:
	TArray<class UMMProjectileOnHitEffect*>* projectileOnHitEffects;

	//Move to timer function - Richmond
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
		int getDamageValue();

	virtual void onHitSpecialEffect(FHitResult hit);

	//Object pooling implementation
	void SetActorActivation(bool state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* parentPool;

	UPROPERTY(BlueprintReadOnly)
		owningFaction faction;

	UFUNCTION(BlueprintImplementableEvent)
		void OnFireEvent();

	void InitializeProjectile(float newDamage, float newProjectileSpeed, bool isProjectileBounce, float gravityScale, TArray<UMMProjectileOnHitEffect*>* newProjectileOnHitEffects, owningFaction newFaction);
protected:
	UFUNCTION()
		void OnLifespanEnd();
};
