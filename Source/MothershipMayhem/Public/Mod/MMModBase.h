// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Mod/MMModDataAsset.h"
#include "MMModBase.generated.h"

USTRUCT(BlueprintType)
struct FModStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) float fireRate;
	UPROPERTY(BlueprintReadWrite) float reloadTime;
	UPROPERTY(BlueprintReadWrite) int maxAmmo;
	UPROPERTY(BlueprintReadWrite) float accuracy;
	UPROPERTY(BlueprintReadWrite) int numberOfProjectilesToShoot;
	UPROPERTY(BlueprintReadWrite) float damage;
	UPROPERTY(BlueprintReadWrite) float projectileSpeed;
	UPROPERTY(BlueprintReadWrite) float projectileGravityScale;
};

/**
 * 
 */
UCLASS(Blueprintable)
class MOTHERSHIPMAYHEM_API UMMModBase : public UObject
{
	GENERATED_BODY()
			
protected:
	//Stats that adds to the base gun stats
	UPROPERTY(BlueprintReadOnly) FModStats additiveModStats;
	//Stats that multiplies to the base gun stats
	UPROPERTY(BlueprintReadOnly) FModStats multiplicativeModStats;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
		FString description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
		MMModType modType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
		MMModSlot modSlot;

	//MOD Projectile for Projectile effect mods ===============
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;

	UPROPERTY(EditAnywhere, Category = Projectile)
		USoundBase* m_shoot_sfx;

	UPROPERTY(EditAnywhere, Category = Projectile)
		USoundBase* m_hit_sfx;
	
	//Called when creating a mod
	UFUNCTION(BlueprintCallable) virtual UMMModBase* InitializeMod(
		UPARAM(DisplayName = "New Additive Mod Stats") FModStats newAdditiveModStats,
		UPARAM(DisplayName = "New Multiplicative Mod Stats") FModStats newMultiplicativeModStats,
		TSubclassOf<class AMMProjectileBase> newProjectileClass,
		FString newName);

	//Called when added a mod to a gun
	UFUNCTION(BlueprintCallable) virtual void AddToGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun);

	//Called when the mod is removed from the gun
	UFUNCTION(BlueprintCallable) virtual void RemoveFromGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun);

	UFUNCTION(BlueprintPure) FModStats GetAdditiveModStats();
	UFUNCTION(BlueprintPure) FModStats GetMultiplicativeModStats();
};
