// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MMGunDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMGunDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
		UStaticMesh* gunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		bool isAutomatic;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float fireRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float maxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float reloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float numberOfProjectilesToShoot;
};
