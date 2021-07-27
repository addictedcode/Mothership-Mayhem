// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MMProjectileOnHitEffect.h"
#include "MMProjectileOnHitSpawnEffect.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMProjectileOnHitSpawnEffect : public UMMProjectileOnHitEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> m_Spawn_Class;
	
	virtual void ApplyEffect(UWorld* world, const FHitResult& Hit) override;
};
