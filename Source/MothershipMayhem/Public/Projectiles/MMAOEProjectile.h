// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MMProjectileBase.h"
#include "MMAOEProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API AMMAOEProjectile : public AMMProjectileBase
{
	GENERATED_BODY()
	
public:
	virtual void onHitSpecialEffect(FHitResult hit) override;

private:
	UPROPERTY(EditAnywhere, Category = AOE)
		float radius = 300.0f;
	UPROPERTY(EditAnywhere, Category = AOE)
		int areaOfEffectDamage = 10;
};
