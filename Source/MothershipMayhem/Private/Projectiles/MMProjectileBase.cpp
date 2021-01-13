// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Projectiles/ProjectilePool.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyStatsComponent.h"

// Sets default values
AMMProjectileBase::AMMProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	projectileMovement->InitialSpeed = 3000.f;
	projectileMovement->MaxSpeed = 3000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;

	// Die after 1.5 seconds by default
	this->lifespan = 20.0f;
	
}

// Called when the game starts or when spawned
void AMMProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMMProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->currentLifePeriod += DeltaTime;
	if (this->currentLifePeriod >= this->lifespan)
	{
		this->currentLifePeriod = 0;
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

		AAICharacter* enemy = Cast<AAICharacter>(OtherActor);
		if (enemy != nullptr)
		{
			UEnemyStatsComponent* enemyStats = enemy->enemyStats;
			if (enemyStats != nullptr) {
				FVector direction = GetVelocity();
				direction.Z = 0;
				direction.Normalize();
				direction.Z = 1.0f;
				enemyStats->ApplyStatusEffect(WET, direction * 500.0f);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("HIT ENEMY DOES NOT HAVE STATS COMPONENT"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Hit target is not an enemy"));
		}
	}
}

void AMMProjectileBase::SetActorActivation(bool state)
{
	this->SetActorHiddenInGame(!state);
	this->SetActorEnableCollision(state);
	this->SetActorTickEnabled(state);

	if (state)
	{
		projectileMovement->UpdatedComponent = RootComponent;
		projectileMovement->Velocity = FVector(GetActorForwardVector() * 3000.0f);
		projectileMovement->SetComponentTickEnabled(true);
	}
}


