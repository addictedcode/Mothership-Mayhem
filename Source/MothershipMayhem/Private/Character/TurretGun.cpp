// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TurretGun.h"
#include "Character/MMCharacterBase.h"
#include "Projectiles/ProjectilePool.h"
#include "Projectiles/MMProjectileBase.h"

// Sets default values
ATurretGun::ATurretGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurretGun::BeginPlay()
{
	Super::BeginPlay();
	
	this->timeToReload = 2.0f;

	AMMCharacterBase* player = Cast<AMMCharacterBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player != nullptr)
	{
		this->target = player;
	}
}

// Called every frame
void ATurretGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->currentReloadTime += DeltaTime;

	if (this->currentReloadTime >= this->timeToReload)
	{
		AttackTarget(target);
	}
}

void ATurretGun::AttackTarget(AActor* targetActor)
{
	if (this->currentReloadTime >= this->timeToReload && !this->IsHidden()) {
		this->currentReloadTime = 0;
		UWorld* const world = this->GetWorld();
		if (world == NULL)
		{
			return;
		}

		//Get Spawn Location and Rotation for the projectile to spawn
		FVector SpawnLocation = this->ProjectileLaunchArea->GetComponentLocation();
		FVector lineToTarget = target->GetActorLocation() - ProjectileLaunchArea->GetComponentLocation();

		FRotator SpawnRotation = lineToTarget.Rotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// spawn the projectile at the muzzle
		if (bulletPool != nullptr)
		{
			AProjectilePool* pool = Cast<AProjectilePool>(bulletPool);
			if (pool != nullptr)
			{
				AMMProjectileBase* projectile = pool->SpawnObject(projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				if (projectile)
				{
					projectile->InitializeProjectile(this->attackDamage, this->projectileSpeed, this->hasBouncingAttack,
						this->projectileGravityScale, nullptr, owningFaction::Neutral);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No Pool Class Reference"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Pool Actor Reference AICharacter"));
		}
	}
}

void ATurretGun::UpdateReloadTime(float newSecPerShot)
{
	this->timeToReload = newSecPerShot;
}

void ATurretGun::UpdateProjectileStats(float damage, float speed, bool isBouncing, float gravityScale)
{
	this->attackDamage = damage;
	this->projectileSpeed = speed;
	this->hasBouncingAttack = isBouncing;
	this->projectileGravityScale = gravityScale;
}

void ATurretGun::SetActorActivation(bool state)
{
	this->SetActorHiddenInGame(!state);
	this->SetActorEnableCollision(state);
	this->SetActorTickEnabled(state);

	if (state)
	{
		this->currentReloadTime = 0;
	}
}

void ATurretGun::SetLaunchArea(UChildActorComponent* launchArea)
{
	this->ProjectileLaunchArea = launchArea;
}

