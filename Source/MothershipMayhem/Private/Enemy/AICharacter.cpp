// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AICharacter.h"

#include "Enemy/EnemyStatsComponent.h"
#include "Projectiles/ProjectilePool.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectiles/MMProjectileBase.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	#pragma region StatsComponent
	enemyStats = CreateDefaultSubobject<UEnemyStatsComponent>(TEXT("StatsComponent"));
	enemyStats->movementComponent = GetCharacterMovement();
	#pragma  endregion
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frameda
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->currentReloadTime += DeltaTime;
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

		AActor* owner = this;
		//Get Spawn Location and Rotation for the projectile to spawn
		FRotator SpawnRotation = owner->GetActorRotation();
		FVector SpawnLocation = owner->GetActorLocation();
		FVector lineToTarget = target->GetActorLocation() - GetMesh()->GetComponentLocation();
		
		if (GetMesh() != nullptr)
		{
			//SpawnRotation = GetMesh()->GetRelativeRotation();
			lineToTarget.Z = 0;
			lineToTarget.Normalize();
			FVector spawnPoint = FVector(100 * lineToTarget.X, 100 * lineToTarget.Y, 100);
			SpawnLocation = GetMesh()->GetComponentLocation() + spawnPoint;
		}

		//Apply Weapon Spread
		const FRotator weaponSpread = FRotator(0,
			0, 0);
		FVector spreadVector = SpawnRotation.Vector();;
		spreadVector = weaponSpread.RotateVector(spreadVector);
		SpawnRotation = lineToTarget.Rotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		// spawn the projectile at the muzzle
		if (bulletPool != nullptr)
		{
			AProjectilePool* pool = Cast<AProjectilePool>(bulletPool);
			if (pool != nullptr)
			{
				pool->SpawnObject(projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
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

