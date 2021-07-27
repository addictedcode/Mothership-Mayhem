// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MMProjectileOnHitEffect.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMProjectileOnHitEffect : public UObject
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect(class UEnemyStatsComponent* enemy, FVector position) {};
	virtual void ApplyEffect(const FHitResult& Hit) {};
};
