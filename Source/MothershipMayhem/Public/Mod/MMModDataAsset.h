// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MMModDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MOTHERSHIPMAYHEM_API UMMModDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_fireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_maxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_reloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_numberOfProjectilesToShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_projectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Additive Stats")
		float add_projectileGravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_fireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_maxAmmo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_reloadTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_accuracy = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_numberOfProjectilesToShoot = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_projectileSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplicative Stats")
		float multiply_projectileGravityScale = 1;
	
};
