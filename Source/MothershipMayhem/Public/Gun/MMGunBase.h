// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stats/MMStatsBase.h"
#include "MMGunBase.generated.h"

struct TGunStats
{
	//Affect Gun
	TMMStatsBase fireRate;
	TMMStatsBase reloadTime;
	TMMStatsBase maxAmmo;
	float currentAmmo = 0;
	TMMStatsBase numberOfProjectilesToShoot;

	//Affect Projectile
	TMMStatsBase damage;
	TMMStatsBase projectileSpeed;
};

UCLASS()
class MOTHERSHIPMAYHEM_API AMMGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//Variables
protected:
	TGunStats gunStats;

//UE Visible Variables
protected:
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* gunMesh;

	// Projectile class to shoot
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMMProjectileBase> projectileClass;
	
//Functions
public:	

	bool OnShoot();

//Get / Set Functions
public:

	TGunStats& GetGunStats() { return gunStats; };
	
	void SetMesh(class UStaticMesh*);
	void SetProjectile(TSubclassOf<class AMMProjectileBase> newProjectileClass);
};
