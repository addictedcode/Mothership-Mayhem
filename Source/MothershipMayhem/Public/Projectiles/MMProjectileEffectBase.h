// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MMProjectileEffectBase.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMProjectileEffectBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect(class UEnemyStatsComponent*, FVector position) {};
};
