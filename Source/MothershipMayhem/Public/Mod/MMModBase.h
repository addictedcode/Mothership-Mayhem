// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MMModBase.generated.h"

USTRUCT(BlueprintType)
struct FModStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly) float fireRate;
	UPROPERTY(BlueprintReadOnly) float reloadTime;
	UPROPERTY(BlueprintReadOnly) float maxAmmo;
	UPROPERTY(BlueprintReadOnly) float accuracy;
	UPROPERTY(BlueprintReadOnly) float numberOfProjectilesToShoot;
	UPROPERTY(BlueprintReadOnly) float damage;
	UPROPERTY(BlueprintReadOnly) float projectileSpeed;
	UPROPERTY(BlueprintReadOnly) float projectileGravityScale;
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
	//Called when creating a mod
	UFUNCTION(BlueprintCallable) virtual void InitializeMod(
		UPARAM(DisplayName = "Additive Mod Stats") FModStats& newAdditiveModStats,
		UPARAM(DisplayName = "Multiplicative Mod Stats") FModStats& newMultiplicativeModStats);

	//Called when added a mod to a gun
	UFUNCTION(BlueprintCallable) virtual void AddToGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun);

	//Called when the mod is removed from the gun
	UFUNCTION(BlueprintCallable) virtual void RemoveFromGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun);

	UFUNCTION(BlueprintPure) FModStats GetAdditiveModStats();
	UFUNCTION(BlueprintPure) FModStats GetMultiplicativeModStats();
};
