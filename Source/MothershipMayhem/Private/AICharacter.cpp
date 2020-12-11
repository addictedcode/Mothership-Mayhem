// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectiles/MMProjectileBase.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
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

void AAICharacter::UpdateWalkSpeed(float newWalkSpeed)
{
	UCharacterMovementComponent* CharaMovement = GetCharacterMovement();
	if (CharaMovement)
	{
		CharaMovement->MaxWalkSpeed = newWalkSpeed;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO character movement component"));
	}
}

void AAICharacter::AttackTarget(AActor* target)
{
	if (this->currentReloadTime >= this->timeToReload) {
		UWorld* const world = this->GetWorld();
		if (world == NULL)
		{
			return;
		}

		AActor* owner = this;
		//Get Spawn Location and Rotation for the projectile to spawn
		FRotator SpawnRotation = owner->GetActorRotation();
		FVector SpawnLocation = owner->GetActorLocation();

		if (GetMesh() != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("OK"));
			//SpawnRotation = GetMesh()->GetRelativeRotation();
			SpawnLocation = GetMesh()->GetComponentLocation() + FVector(0, 0, 100);
		}

		//Apply Weapon Spread
		const FRotator weaponSpread = FRotator(0,
			0, 0);
		FVector spreadVector = SpawnRotation.Vector();;
		spreadVector = weaponSpread.RotateVector(spreadVector);
		SpawnRotation = spreadVector.Rotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// spawn the projectile at the muzzle
		AActor* newProjectile = world->SpawnActor<AMMProjectileBase>(projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		this->currentReloadTime = 0;
	}
}

