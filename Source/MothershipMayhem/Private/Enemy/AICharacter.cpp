// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AICharacter.h"

#include "Enemy/EnemyStatsComponent.h"
#include "Projectiles/ProjectilePool.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectiles/MMProjectileBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	#pragma region StatsComponent
	enemyStats = CreateDefaultSubobject<UEnemyStatsComponent>(TEXT("StatsComponent"));
	enemyStats->movementComponent = GetCharacterMovement();
	#pragma  endregion

	#pragma region ProjectileLaunchArea
	ProjectileLaunchArea = CreateDefaultSubobject<UChildActorComponent>(TEXT("ProjectileLaunchArea"));
	ProjectileLaunchArea->SetupAttachment(GetMesh());
	#pragma endregion
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	this->timeToReload = 2.0f;
}

// Called every frameda
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->currentReloadTime += DeltaTime;

	if (isBeingSucked) {
		this->SetActorLocation(UKismetMathLibrary::VInterpTo(this->GetActorLocation(), player->GetActorLocation(), DeltaTime, 1.0f), false,
			nullptr, ETeleportType::TeleportPhysics);

		if (FVector::Dist(player->GetActorLocation(), this->GetActorLocation()) < 100.0f) {
			this->enemyStats->TakeDamage(999999);
		}
	}
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//Changes MaxWalkSpeed of movement component
void AAICharacter::UpdateWalkSpeed(float newWalkSpeed)
{
	UCharacterMovementComponent* CharaMovement = GetCharacterMovement();
	if (CharaMovement)
	{
		CharaMovement->MaxWalkSpeed = newWalkSpeed * this->moveSpeedMultiplier;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player has no character movement component"));
	}
}
//Checks if AICharacter is not stunned and is not reloading then shoots at target
void AAICharacter::AttackTarget(AActor* target)
{
	if (this->currentReloadTime >= this->timeToReload && !this->isStunned && !this->IsHidden()) {
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
						this->projectileGravityScale, nullptr, owningFaction::Enemy);
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
UEnemyStatsComponent* AAICharacter::getEnemyStats()
{
	return this->enemyStats;
}
//Changes multiplier applied to movement component MaxWalkSpeed and applies the net change to current setting if new multiplier is different from old one
void AAICharacter::ChangeSpeedMultiplier(float multiplier)
{
	UCharacterMovementComponent* CharaMovement = GetCharacterMovement();
	if (CharaMovement)
	{
		float multiplierChange = multiplier / this->moveSpeedMultiplier;
		CharaMovement->MaxWalkSpeed *= multiplierChange;
		this->moveSpeedMultiplier = multiplier;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player has no character movement component"));
	}
}

void AAICharacter::UpdateReloadTime(float newSecPerShot)
{
	this->timeToReload = newSecPerShot;
}

void AAICharacter::UpdateProjectileStats(float damage, float speed, bool isBouncing, float gravityScale)
{
	this->attackDamage = damage;
	this->projectileSpeed = speed;
	this->hasBouncingAttack = isBouncing;
	this->projectileGravityScale = gravityScale;
}

//Function for object pooling implementation
void AAICharacter::SetActorActivation(bool state)
{
	this->SetActorHiddenInGame(!state);
	this->SetActorEnableCollision(state);
	this->SetActorTickEnabled(state);

	if (state)
	{
		this->isStunned = false;
		this->currentReloadTime = 0;
		this->enemyStats->ResetComponent();
	}
}

void AAICharacter::SuckIntoVacuum(AActor* playerPtr, int executeThreshold)
{
	if (this->enemyStats->getCurrentHP() <= executeThreshold) {
		GetCharacterMovement()->SetComponentTickEnabled(false);

		player = playerPtr;
		this->bSimGravityDisabled = true;
		this->isStunned = true;
		isBeingSucked = true;
	}
}

bool AAICharacter::isKnockbackImmune()
{
	return this->isImmuneToKnockback;
}

