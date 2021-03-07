// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMesh* CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		int MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		int MaxFameMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxFameAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxFameAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float SecPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxFameSecPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float projectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		bool isBouncingProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float projectileGravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxFameRunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxFameWalkSpeed;
};
