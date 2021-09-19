// Fill out your copyright notice in the Description page of Project Settings.


#include "MothershipMayhem/Public/Gun/MMGunBase.h"
#include "Projectiles/ProjectilePool.h"
#include "Projectiles/MMProjectileBase.h"
#include "Mod/MMModBase.h"
#include "Character/MMCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyStatsComponent.h"

// Sets default values
AMMGunBase::AMMGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	skeletalGunMesh = 
			CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Gun Mesh"));
	skeletalGunMesh->bCastDynamicShadow = false;
	skeletalGunMesh->CastShadow = false;
	skeletalGunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = skeletalGunMesh;



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

void AMMGunBase::SetSkeletalMesh(USkeletalMesh* newSkeletalMesh)
{
	if (skeletalGunMesh != NULL)
	{
		skeletalGunMesh->SetSkeletalMesh(newSkeletalMesh);
	}
}
void AMMGunBase::SetProjectile(TSubclassOf<AMMProjectileBase> newProjectileClass)
{
	projectileClass = newProjectileClass;
	
}
void AMMGunBase::SetDefaultProjectile(TSubclassOf<AMMProjectileBase> newProjectileClass)
{
	defaultProjectileClass = newProjectileClass;
}

void AMMGunBase::SetVacuumMod(bool isVacuumModded)
{
	isVacuum = isVacuumModded;
	isVacuumShooting = false;

	if (isVacuumModded) {
		gunStats.currentAmmo = 0;
		gunStats.damage.AddMultiplicativeModifier(2);
	}
	else {
		gunStats.currentAmmo = gunStats.maxAmmo.GetFinalValue();
		float x = 2;
		gunStats.damage.RemoveMultiplicativeModifier(x);
	}
}

void AMMGunBase::SetMuzzleFlash(UNiagaraSystem* newMuzzleFlashFX)
{
	muzzleFlashFX = newMuzzleFlashFX;
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

	if (GetWorld()->GetTimerManager().IsTimerActive(reloadTimerHandle))
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
	this->PlayReloadAnimation();
	PlayReloadSFX();
	
	GetWorld()->GetTimerManager().SetTimer
	(reloadTimerHandle, this, &AMMGunBase::Reload, gunStats.reloadTime.GetFinalValue());
	
}

bool AMMGunBase::AddMod(UMMModBase* newMod)
{

	for (auto& mod : modList)
	{
		if (newMod->modSlot == mod->modSlot)
			return false;
	}
	
	newMod->AddToGun(this);
	modList.Add(newMod);
	if (newMod->modSlot == MMModSlot::Projectile) {
		this->SetProjectile(newMod->projectileClass);
	}

	return true;

}

void AMMGunBase::RemoveModByMod(UMMModBase* mod)
{
	const int index = modList.Find(mod);
	RemoveModByIndex(index);
}


UMMModBase* AMMGunBase::RemoveModByIndex(int index)
{
	UMMModBase* removedMod = modList[index];
	removedMod->RemoveFromGun(this);
	modList.RemoveAt(index);
	// if the mod at index 0 is removed, update new projectile with the new mod at index 0
	if (modList.Num() > 0) {
		if (index == 0) {
			SetProjectile(modList[0]->projectileClass);
		}
	}
	else if(modList.Num() == 0){
		SetProjectile(defaultProjectileClass);
		UE_LOG(LogTemp, Error, TEXT("Projectile reset!"));
	}
	UE_LOG(LogTemp, Error, TEXT("gamer!"));

	return removedMod;
}

void AMMGunBase::OnDraw()
{
	
}

void AMMGunBase::OnHolster()
{
	/*if (isReloading)
		m_current_reload_sfx->Stop();

	isReloading = false;
	isShooting = false;*/

	//if(m_current_reload_sfx != NULL)
	//	if(m_current_reload_sfx)
	//		if(m_current_reload_sfx->IsPlaying())
	//			m_current_reload_sfx->Stop();


	GetWorld()->GetTimerManager().ClearTimer(reloadTimerHandle);
}


#pragma endregion 

void AMMGunBase::PlayShootSFX()
{
	/*if (!m_shoot_sfx) return;
	
	UGameplayStatics::PlaySoundAtLocation(this, m_shoot_sfx, this->GetTransform().GetLocation());*/
}

void AMMGunBase::PlayReloadSFX()
{
	/*if (!m_reload_sfx) return;
	if(isReloading)
	m_current_reload_sfx = UGameplayStatics::SpawnSoundAttached(m_reload_sfx, RootComponent);*/
}

void AMMGunBase::PrimaryShoot()
{
	if (!isShooting)
	{
		GetWorld()->GetTimerManager().ClearTimer(primaryShootTimerHandle);
		return;
	}

	if (gunStats.currentAmmo > 0 || isVacuum) {
		if (isReloading)
		{
			GetWorld()->GetTimerManager().ClearTimer(reloadTimerHandle);
		}
		if (!isVacuum || isVacuumShooting) {
			for (int i = 0; i < gunStats.numberOfProjectilesToShoot.GetFinalValue(); ++i) {
				//UE_LOG(LogTemp, Error, TEXT("Bang!"));
				ShootProjectile();
				// play sound ===
				PlayShootSFX();
				AMMCharacterBase* characterParent =
					Cast<AMMCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				if (characterParent != NULL) {
					this->PlayRecoilAnimation();
				}
				else {
					UE_LOG(LogTemp, Error, TEXT("No Character"));
				}

			}
			gunStats.currentAmmo--;
		}
		else {//vacuum gun behavior
			if (vacuumHitbox != nullptr) {
				TArray<AActor*> actors;
				vacuumHitbox->GetOverlappingActors(actors);
				for (int i = 0; i < actors.Num(); i++) {
					AAICharacter* enemyInRange = Cast<AAICharacter>(actors[i]);
					if (enemyInRange) {
						enemyInRange->SuckIntoVacuum(Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()), 10);//execute anyone at or below 10 hp
						gunStats.currentAmmo++;
					}
				}

				if (gunStats.currentAmmo >= gunStats.maxAmmo.GetFinalValue()) {
					isVacuumShooting = true;
				}
			}
		}
	}
	
	if (gunStats.currentAmmo <= 0)
	{
		if (!isVacuum) {
			GetWorld()->GetTimerManager().ClearTimer(primaryShootTimerHandle);
			OnReload();
		}
		else {
			isVacuumShooting = false;
		}
	}
	
}


bool AMMGunBase::ShootProjectile()
{
	UWorld* const world = this->GetWorld();

	if (world == NULL)
	{
		return false;
	}

	if (!skeletalGunMesh->DoesSocketExist("MuzzlePoint"))
	{
		return false;
	}
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
				gunStats.isBouncingProjectile, gunStats.projectileGravityScale.GetFinalValue(), &projectileOnHitEffects, owningFaction::Player, m_hit_sfx);
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
	/*if (isReloading) {
		m_current_reload_sfx->Stop();
	}*/
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

