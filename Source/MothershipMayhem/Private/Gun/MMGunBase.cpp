// Fill out your copyright notice in the Description page of Project Settings.


#include "MothershipMayhem/Public/Gun/MMGunBase.h"
#include "Projectiles/MMProjectileBase.h"

// Sets default values
AMMGunBase::AMMGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	#pragma region Gun Mesh
	// Create a gun mesh component
	gunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("gunMesh"));
	gunMesh->bCastDynamicShadow = false;
	gunMesh->CastShadow = false;
	gunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = gunMesh;
	#pragma endregion 
}

// Called when the game starts or when spawned
void AMMGunBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMMGunBase::SetMesh(UStaticMesh* newStaticMesh)
{
	if (gunMesh != NULL)
	{
		gunMesh->SetStaticMesh(newStaticMesh);
	}
}

void AMMGunBase::SetProjectile(TSubclassOf<AMMProjectileBase> newProjectileClass)
{
	projectileClass = newProjectileClass;
}


#pragma region Inputs
void AMMGunBase::OnPrimaryShootPressed()
{
	isShooting = true;
	accuracyAngle = 45 - (45 * (gunStats.accuracy.GetFinalValue() / 100));
	
	if (projectileClass == NULL)
	{
		return;
	}

	if (GetWorld()->GetTimerManager().IsTimerActive(primaryShootTimerHandle))
	{
		return;
	}
	
	GetWorld()->GetTimerManager().SetTimer
	(primaryShootTimerHandle, this, &AMMGunBase::PrimaryShoot, gunStats.fireRate.GetFinalValue(), gunStats.isAutomatic, 0.0f);
}

void AMMGunBase::OnPrimaryShootReleased()
{
	isShooting = false;
}

void AMMGunBase::OnReload()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(reloadTimerHandle))
	{
		return;
	}

	isReloading = true;
	
	GetWorld()->GetTimerManager().SetTimer
	(reloadTimerHandle, this, &AMMGunBase::Reload, gunStats.reloadTime.GetFinalValue());
}

void AMMGunBase::OnDraw()
{
	
}

void AMMGunBase::OnHolster()
{
	isReloading = false;
	isShooting = false;
	
	GetWorld()->GetTimerManager().ClearTimer(reloadTimerHandle);
}


#pragma endregion 

void AMMGunBase::PrimaryShoot()
{
	if (!isShooting)
	{
		GetWorld()->GetTimerManager().ClearTimer(primaryShootTimerHandle);
		return;
	}

	if (gunStats.currentAmmo > 0) {
		if (isReloading)
		{
			GetWorld()->GetTimerManager().ClearTimer(reloadTimerHandle);
		}
		for (int i = 0; i < gunStats.numberOfProjectilesToShoot.GetFinalValue(); ++i) {
		        ShootProjectile();
		}
		gunStats.currentAmmo--;
	}
	
	if (gunStats.currentAmmo <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(primaryShootTimerHandle);
		OnReload();
	}
}


bool AMMGunBase::ShootProjectile()
{
	UWorld* const world = this->GetWorld();

	if (world == NULL)
	{
		return false;
	}

	if (!gunMesh->DoesSocketExist("MuzzlePoint"))
	{
		return false;
	}

	//Get Spawn Location and Rotation for the projectile to spawn
	FRotator SpawnRotation = gunMesh->GetSocketRotation("MuzzlePoint");
	const FVector SpawnLocation = gunMesh->GetSocketLocation("MuzzlePoint");

	//Apply Weapon Spread
	const FRotator weaponSpread = FRotator(FMath::RandRange(-accuracyAngle, accuracyAngle), 
		FMath::RandRange(-accuracyAngle, accuracyAngle), FMath::RandRange(-accuracyAngle, accuracyAngle));
	FVector spreadVector = SpawnRotation.Vector();;
	spreadVector = weaponSpread.RotateVector(spreadVector);
	SpawnRotation = spreadVector.Rotation();
	
	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// spawn the projectile at the muzzle
	AActor* newProjectile = world->SpawnActor<AMMProjectileBase>(projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	
	if (!newProjectile)
	{
		return false;
	}
	return true;
}

void AMMGunBase::Reload()
{
	gunStats.currentAmmo = gunStats.maxAmmo.GetFinalValue();
	isReloading = false;
	if (isShooting)
	{
		OnPrimaryShootPressed();
	}
}
