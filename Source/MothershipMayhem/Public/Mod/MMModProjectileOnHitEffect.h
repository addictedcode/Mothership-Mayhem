// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mod/MMModBase.h"
#include "MMModProjectileOnHitEffect.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMModProjectileOnHitEffect : public UMMModBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMMProjectileOnHitEffect* projectileOnHitEffect;
	
	//Called when added a mod to a gun
	virtual void AddToGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun) override;

	//Called when the mod is removed from the gun
	virtual void RemoveFromGun(
		UPARAM(DisplayName = "Gun") class AMMGunBase* gun) override;
};
