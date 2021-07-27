// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MMProjectileBase.h"
#include "MMProjectileTurretMaker.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API AMMProjectileTurretMaker : public AMMProjectileBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = turret)
		TSubclassOf<class ATurretGun> turretClass;

	virtual void onHitSpecialEffect() override;
};
