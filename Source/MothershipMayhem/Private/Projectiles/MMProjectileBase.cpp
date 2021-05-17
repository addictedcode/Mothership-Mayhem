// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Projectiles/ProjectilePool.h"
#include "Projectiles/MMProjectileEffectBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyStatsComponent.h"

// Sets default values
AMMProjectileBase::AMMProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Use a sphere as a simple collision representation
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	collisionComp->InitSphereRadius(5.0f);
	collisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	collisionComp->OnComponentHit.AddDynamic(this, &AMMProjectileBase::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	collisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = collisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileComp"));
	projectileMovement->UpdatedComponent = collisionComp;
	projectileMovement->MaxSpeed = 3000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;
	projectileMovement->ProjectileGravityScale = 1;

	// Die after 20 seconds by default
	this->lifespan = 20.0f;
	
}

// Called when the game starts or when spawned
void AMMProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
//void AMMProjectileBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	this->currentLifePeriod += DeltaTime;
//	if (this->currentLifePeriod >= this->lifespan)
//	{
//		this->currentLifePeriod = 0;
//		if (parentPool != nullptr) {
//			AProjectilePool* pool = Cast<AProjectilePool>(parentPool);
//			if (pool != nullptr) {
//				pool->ReturnObject(this);
//				this->SetActorActivation(false);
//			}
//			else
//			{
//				UE_LOG(LogTemp, Error, TEXT("No Pool Class Reference"));
//			}
//		}
//		else
//		{
//			UE_LOG(LogTemp, Error, TEXT("No Pool Actor Reference"));
//		}
//	}
//}

void AMMProjectileBase::InitializeProjectile(float newDamage, float newProjectileSpeed, bool isProjectileBounce, float gravityScale, TArray<UMMProjectileEffectBase*>* newProjectileEffects, owningFaction newFaction)
{
	damage = newDamage;
	projectileSpeed = newProjectileSpeed;
	projectileEffects = newProjectileEffects;
	projectileMovement->bShouldBounce = isProjectileBounce;
	projectileMovement->ProjectileGravityScale = gravityScale;
	faction = newFaction;
}

void AMMProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (parentPool != nullptr) {
			AProjectilePool* pool = Cast<AProjectilePool>(parentPool);
			if (pool != nullptr) {
				pool->ReturnObject(this);
				this->SetActorActivation(false);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("PROJECTILEBASE ONHIT: No Pool Class Reference"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PROJECTILEBASE ONHIT: No Pool Actor Reference"));
		}
		if (faction == owningFaction::Player) {
			AAICharacter* enemy = Cast<AAICharacter>(OtherActor);
			if (enemy != nullptr)
			{
				UEnemyStatsComponent* enemyStats = enemy->enemyStats;
				if (enemyStats != nullptr) {
					enemyStats->TakeDamage(damage);
					//enemyStats->ApplyStatusEffect(DISORIENTED);

					//Calls all ApplyEffects (MMProjectileEffectBase) from a pointer to the MMGunBase class, projectileEffects TArray
					if (projectileEffects != nullptr) {
						for (UMMProjectileEffectBase* effect : *projectileEffects)
						{
							effect->ApplyEffect(enemyStats, Hit.ImpactPoint);
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("HIT ENEMY DOES NOT HAVE STATS COMPONENT"));
				}
			}
			else
			{
				//UE_LOG(LogTemp, Error, TEXT("Hit target is not an enemy"));
			}
		}
	}
	else{
		if (parentPool != nullptr) {
			AProjectilePool* pool = Cast<AProjectilePool>(parentPool);
			if (pool != nullptr) {
				pool->ReturnObject(this);
				this->SetActorActivation(false);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("PROJECTILEBASE ONHIT: No Pool Class Reference"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PROJECTILEBASE ONHIT: No Pool Actor Reference"));
		}
	}
	
}

void AMMProjectileBase::SetActorActivation(bool state)
{
	this->SetActorHiddenInGame(!state);
	this->SetActorEnableCollision(state);
	//this->SetActorTickEnabled(state);

	if (state)
	{
		projectileMovement->UpdatedComponent = RootComponent;
		projectileMovement->Velocity = FVector(GetActorForwardVector() * projectileSpeed);
		projectileMovement->MaxSpeed = projectileSpeed;
		GetWorld()->GetTimerManager().SetTimer(projectileLifespanTimerHandle, this, &AMMProjectileBase::OnLifespanEnd, lifespan);
		projectileMovement->SetComponentTickEnabled(true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void AMMProjectileBase::OnLifespanEnd()
{
	if (parentPool != nullptr) {
		AProjectilePool* pool = Cast<AProjectilePool>(parentPool);
		if (pool != nullptr) {
			pool->ReturnObject(this);
			this->SetActorActivation(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Pool Class Reference"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Pool Actor Reference"));
	}
}
