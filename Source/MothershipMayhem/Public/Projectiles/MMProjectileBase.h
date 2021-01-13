// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MMProjectileBase.generated.h"

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
public:
	//Move to timer function - Richmond
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Object pooling implementation
	void SetActorActivation(bool state);
	AActor* parentPool;

protected:
	UFUNCTION()
		void OnLifespanEnd();
};
