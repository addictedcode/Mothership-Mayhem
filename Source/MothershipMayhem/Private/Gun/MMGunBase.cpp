// Fill out your copyright notice in the Description page of Project Settings.


#include "MothershipMayhem/Public/Gun/MMGunBase.h"
#include "Projectiles/ProjectilePool.h"
#include "Projectiles/MMProjectileBase.h"
#include "Mod/MMModBase.h"
#include "Character/MMCharacterBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMMGunBase::AMMGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	#pragma region Gun Mesh
	// Create a gun mesh component
	/*gunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("gunMesh"));
	gunMesh->bCastDynamicShadow = false;
	gunMesh->CastShadow = false;
	gunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = gunMesh;*/

	skeletalGunMesh = 
			CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("skeletalGunMesh"));
	skeletalGunMesh->bCastDynamicShadow = false;
	skeletalGunMesh->CastShadow = false;
	skeletalGunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = skeletalGunMesh;

	/*static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT
			("AnimSequence'/Game/Assets/Animations/pistolSkeletal_2_Skeleton_Sequence.pistolSkeletal_2_Skeleton_Sequence'"));
	
	recoilAnimation = anim.Object;*/

	#pragma endregion 
}

// Called when the game starts or when spawned
void AMMGunBase::BeginPlay()
{
	Super::BeginPlay();
}


FGunStats AMMGunBase::GetStats()
{
	// make sure to include the final values later on

	FGunStats statsToReturn;

	statsToReturn.fireRate = gunStats.fireRate.GetBaseValue();
	statsToReturn.reloadTime = gunStats.reloadTime.GetBaseValue();

	statsToReturn.maxAmmo = gunStats.maxAmmo.GetBaseValue();
	//statsToReturn.currentAmmo = gunStats.accuracy.GetBaseValue();
	statsToReturn.currentAmmo = gunStats.currentAmmo; // THIS IS ONLY FOR TESTING

	statsToReturn.accuracy = gunStats.accuracy.GetBaseValue(); 
	statsToReturn.isAutomatic = gunStats.isAutomatic;
	
	statsToReturn.numberOfProjectilesToShoot = gunStats.numberOfProjectilesToShoot.GetBaseValue();

	statsToReturn.damage = gunStats.damage.GetBaseValue();
	statsToReturn.projectileSpeed = gunStats.projectileSpeed.GetBaseValue();

	return statsToReturn;
}
FGunStats AMMGunBase::GetFinalStats()
{
	// make sure to include the final values later on

	FGunStats statsToReturn;

	statsToReturn.fireRate = gunStats.fireRate.GetFinalValue();
	statsToReturn.reloadTime = gunStats.reloadTime.GetFinalValue();

	statsToReturn.maxAmmo = gunStats.maxAmmo.GetFinalValue();
	//statsToReturn.currentAmmo = gunStats.accuracy.GetBaseValue();
	statsToReturn.currentAmmo = gunStats.currentAmmo; // THIS IS ONLY FOR TESTING

	statsToReturn.accuracy = gunStats.accuracy.GetFinalValue();
	statsToReturn.isAutomatic = gunStats.isAutomatic;

	statsToReturn.numberOfProjectilesToShoot = gunStats.numberOfProjectilesToShoot.GetBaseValue();

	statsToReturn.damage = gunStats.damage.GetFinalValue();
	statsToReturn.projectileSpeed = gunStats.projectileSpeed.GetFinalValue();

	return statsToReturn;
}

TArray<UMMModBase*>& AMMGunBase::GetModList()
{
	return modList;
}

void AMMGunBase::SetMesh(UStaticMesh* newStaticMesh)
{
	if (gunMesh != NULL)
	{
		gunMesh->SetStaticMesh(newStaticMesh);
	}
}

void AMMGunBase::SetSkeletalMesh(USkeletalMesh* newSkeletalMesh)
{
	if (skeletalGunMesh != NULL)
	{
		skeletalGunMesh->SetSkeletalMesh(newSkeletalMesh);
	}
}

void AMMGunBase::SetRecoilAnimation(UAnimSequence* newRecoilAnim)
{
	if (recoilAnimation != NULL)
	{
		recoilAnimation = newRecoilAnim;
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

void AMMGunBase::AddMod(UMMModBase* newMod)
{
	newMod->AddToGun(this);
	modList.Add(newMod);
}

void AMMGunBase::RemoveModByMod(UMMModBase* mod)
{
	const int index = modList.Find(mod);
	RemoveModByIndex(index);
}

UMMModBase* AMMGunBase::RemoveModByIndex(int index)
{
	UMMModBase* removedMod = modList[index];
	modList.RemoveAt(index);
	return removedMod;
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
			//UE_LOG(LogTemp, Error, TEXT("Bang!"));
		    ShootProjectile();
			// play sound ===
			AMMCharacterBase* characterParent = 
					Cast<AMMCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (characterParent != NULL) {
				characterParent->PlayShootingSound();
				this->PlayRecoilAnimation();
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("No Character"));
			}
				
		}
		gunStats.currentAmmo--;
	}
	
	if (gunStats.currentAmmo <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(primaryShootTimerHandle);
		OnReload();
	}

	/*bool bLoop = false;
	if (skeletalGunMesh != NULL) {
		if (recoilAnimation != NULL) {
			skeletalGunMesh->PlayAnimation(recoilAnimation, bLoop);
			UE_LOG(LogTemp, Error, TEXT("Recoil! %s"), *recoilAnimation->GetFName().ToString());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("No Recoil!"));
		}
	}*/
	
}


bool AMMGunBase::ShootProjectile()
{
	UWorld* const world = this->GetWorld();

	if (world == NULL)
	{
		return false;
	}

	/*if (!gunMesh->DoesSocketExist("MuzzlePoint"))
	{
		return false;
	}*/

	if (!skeletalGunMesh->DoesSocketExist("MuzzlePoint"))
	{
		return false;
	}

	//Get Spawn Location and Rotation for the projectile to spawn
	/*FRotator SpawnRotation = gunMesh->GetSocketRotation("MuzzlePoint");
	const FVector SpawnLocation = gunMesh->GetSocketLocation("MuzzlePoint");*/

	FRotator SpawnRotation = skeletalGunMesh->GetSocketRotation("MuzzlePoint");
	const FVector SpawnLocation = skeletalGunMesh->GetSocketLocation("MuzzlePoint");

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
	if (*bulletPool != nullptr)
	{
		AProjectilePool* pool = Cast<AProjectilePool>(*bulletPool);
		if (pool != nullptr)
		{
			AMMProjectileBase* projectile = pool->SpawnObject(projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (!projectile)
				return false;
			projectile->InitializeProjectile(gunStats.damage.GetFinalValue(), gunStats.projectileSpeed.GetFinalValue(), 
				gunStats.isBouncingProjectile, gunStats.projectileGravityScale.GetFinalValue(), &projectileEffects, owningFaction::Player);
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

void AMMGunBase::UpdateStats(int index, int attack, float fireRate, float reloadSpeed, int magazineSize, float accuracy) {

	this->gunStats.damage.RemoveAllAdditionModifiers();
	this->gunStats.fireRate.RemoveAllMultiplicativeModifiers();
	this->gunStats.reloadTime.RemoveAllMultiplicativeModifiers();
	this->gunStats.maxAmmo.RemoveAllAdditionModifiers();

	this->gunStats.damage.AddAdditionModifier(attack);
	this->gunStats.fireRate.AddMultiplicativeModifier(fireRate);
	this->gunStats.reloadTime.AddMultiplicativeModifier(reloadSpeed);
	this->gunStats.maxAmmo.AddAdditionModifier(magazineSize);
	//this->gunStats.accuracy.AddMultiplicativeModifier(accuracy);
	this->Reload();
	UE_LOG(LogTemp, Error, TEXT("Gun Updated"));
}

