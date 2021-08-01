// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MMProjectileBase.h"
#include "MMProjectileObjectMaker.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API AMMProjectileObjectMaker : public AMMProjectileBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = ObjectSpawn)
		TSubclassOf<class AActor> actorBP;
	UPROPERTY(EditAnywhere, Category = ObjectSpawn)
		bool needsProjectilePool = false;

	virtual void onHitSpecialEffect() override;
};
