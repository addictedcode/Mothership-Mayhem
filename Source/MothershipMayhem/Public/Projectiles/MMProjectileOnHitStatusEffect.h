// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MMProjectileOnHitEffect.h"
#include "Enemy/EnemyStatsComponent.h"
#include "MMProjectileOnHitStatusEffect.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMProjectileOnHitStatusEffect : public UMMProjectileOnHitEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<StatusEffects> statusEffect;
	virtual void ApplyEffect(class UEnemyStatsComponent* enemy, FVector position) override;
};
