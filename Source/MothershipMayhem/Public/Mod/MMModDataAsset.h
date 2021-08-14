// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy/EnemyStatsComponent.h"
#include "Projectiles/MMProjectileOnHitEffect.h"
#include "MMModDataAsset.generated.h"

UENUM(BlueprintType)
enum class MMModType : uint8
{
	Basic = 0 UMETA(DisplayName = "Basic"),
	ProjectileEffect = 1 UMETA(DisplayName = "ProjectileEffect"),
	Legendary = 2 UMETA(DisplayName = "Legendary"),
};

UENUM(BlueprintType)
enum class MMModSlot : uint8
{
	Barrel		UMETA(DisplayName = "Barrel"),
	Projectile	UMETA(DisplayName = "Projectile"),
	Magazine	UMETA(DisplayName = "Magazine"),
	Stock		UMETA(DisplayName = "Stock"),
	Legendary	UMETA(DisplayName = "Legendary"),
};

UENUM(BlueprintType)
enum class MMProjectileOnHitEffectType : uint8
{
	None			UMETA(DisplayName = "None"),
	StatusEffect	UMETA(DisplayName = "StatusEffect"),
	SpawnEffect		UMETA(DisplayName = "SpawnEffect"),
};
/**
 * 
 */
UCLASS(BlueprintType)
class MOTHERSHIPMAYHEM_API UMMModDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
		MMModType modType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
		MMModSlot modSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
		FString description;

	//PROJECTILE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (EditCondition = "modSlot == MMModSlot::Projectile", EditConditionHides))
		TSubclassOf<class AMMProjectileBase> projectileClass;


	#pragma region Additive Stats
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
	#pragma endregion 

	#pragma region Multiplicative Stats
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
	#pragma endregion

	#pragma region Projectile On Hit Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile On Hit Effect", 
		meta = (EditCondition = "modType == MMModType::ProjectileEffect", EditConditionHides))
	
		MMProjectileOnHitEffectType projectileOnHitEffectType = MMProjectileOnHitEffectType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile On Hit Effect", 
		meta = (EditCondition = "modType == MMModType::ProjectileEffect && projectileOnHitEffectType == MMProjectileOnHitEffectType::StatusEffect", EditConditionHides))
	
		StatusEffects projectileStatusEffect = StatusEffects::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile On Hit Effect",
		meta = (EditCondition = "modType == MMModType::ProjectileEffect && projectileOnHitEffectType == MMProjectileOnHitEffectType::SpawnEffect", EditConditionHides))
		TSubclassOf<AActor> projectileOnHitSpawnClass;
	#pragma endregion

};