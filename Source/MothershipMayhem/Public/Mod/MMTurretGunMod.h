// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mod/MMModBase.h"
#include "MMTurretGunMod.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMTurretGunMod : public UMMModBase
{
	GENERATED_BODY()
	
	virtual UMMModBase* InitializeMod(
		TSubclassOf<class AMMProjectileBase> newProjectileClass);

	virtual void AddToGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun) override;

	virtual void RemoveFromGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun) override;

private:
	float numProjectilesMultiplier;
	float maxAmmoMultiplier;
};
