// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Stats/MMStatsBase.h"
#include "NiagaraSystem.h"
#include "MMGunBase.generated.h"

struct TGunStats
{
	//Affect Gun
	TMMStatsBase fireRate;
	TMMStatsBase reloadTime;
	TMMStatsBase maxAmmo;
	float currentAmmo = 0;
	TMMStatsBase accuracy;
	bool isAutomatic;
	TMMStatsBase numberOfProjectilesToShoot;

	//Affect Projectile
	TMMStatsBase damage;
	TMMStatsBase projectileSpeed;
	bool isBouncingProjectile;
	TMMStatsBase projectileGravityScale;
};


USTRUCT(BlueprintType)
struct FGunStats
{

	GENERATED_USTRUCT_BODY()

	//Affect Gun
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float fireRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float reloadTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float maxAmmo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float currentAmmo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float accuracy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isAutomatic;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float numberOfProjectilesToShoot;

	//Affect Projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float projectileSpeed;
};

UCLASS()
class MOTHERSHIPMAYHEM_API AMMGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//Variables
protected:
	
	TGunStats gunStats;

	UPROPERTY(BlueprintReadOnly) TArray<class UMMModBase*> modList;
	
	FTimerHandle primaryShootTimerHandle;
	bool isShooting = false;

	FTimerHandle reloadTimerHandle;
	bool isReloading = false;

	float accuracyAngle;

	bool isVacuum = false;
	bool isVacuumShooting = false;

public:
	//object pool for the bullets
	AActor** bulletPool;
  
	UBoxComponent* vacuumHitbox;
  
	TArray<class UMMProjectileOnHitEffect*> projectileOnHitEffects;
	
//UE Visible Variables
protected:
	/** Gun mesh: 1st person view (seen only by self) */

	UPROPERTY(BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* skeletalGunMesh;

	UPROPERTY(BlueprintReadWrite, Category = Mesh)
		class UNiagaraSystem* muzzleFlashFX;

	// Projectile class to shoot
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> defaultProjectileClass;
	
//Functions
public:	

	void OnPrimaryShootPressed();
	void OnPrimaryShootReleased();

	void OnHolster();
	void OnDraw();
	
	void OnReload();

	UFUNCTION(BlueprintCallable) void AddMod(class UMMModBase* newMod);
	UFUNCTION(BlueprintCallable) void RemoveModByMod(class UMMModBase* mod);
	UFUNCTION(BlueprintCallable) class UMMModBase* RemoveModByIndex(int index);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayRecoilAnimation();

protected:

	UFUNCTION()
		void PrimaryShoot();
	bool ShootProjectile();

	UFUNCTION()
		void Reload();
	
//Get / Set Functions
public:

	int ammo = 10; // THIS IS ONLY FOR TESTING

	UFUNCTION(BlueprintCallable)
		FGunStats GetStats();
	UFUNCTION(BlueprintCallable)
		FGunStats GetFinalStats();

	UFUNCTION(BlueprintPure) TArray<class UMMModBase*>& GetModList();

	void UpdateStats(int index,
		int attack,
		float fireRate,
		float reloadSpeed,
		int magazineSize,
		float accuracy);

	TGunStats& GetGunStats() { return gunStats; };
	
	void SetSkeletalMesh(class USkeletalMesh*);
	void SetMuzzleFlash(class UNiagaraSystem*);
	void SetProjectile(TSubclassOf<class AMMProjectileBase> newProjectileClass);
	void SetDefaultProjectile(TSubclassOf<class AMMProjectileBase> newProjectileClass);
	void SetVacuumMod(bool isVacuumModded);
};
