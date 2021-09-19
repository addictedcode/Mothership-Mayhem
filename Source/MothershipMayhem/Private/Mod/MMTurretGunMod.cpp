// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod/MMTurretGunMod.h"
#include "Gun/MMGunBase.h"

#include "Mod/MMModFactory.h"

UMMModBase* UMMTurretGunMod::InitializeMod(TSubclassOf<class AMMProjectileBase> newProjectileClass)
{
	name = "Turret Gun";
	projectileClass = newProjectileClass;
	return this;
}

void UMMTurretGunMod::AddToGun(AMMGunBase* gun)
{
	TGunStats& gunStats = gun->GetGunStats();
	this->numProjectilesMultiplier = 1.0f / gunStats.numberOfProjectilesToShoot.GetFinalValue();
	this->maxAmmoMultiplier = 1.0f / gunStats.maxAmmo.GetFinalValue();
	//Multiplicative Stats
	if (multiplicativeModStats.accuracy != 1)
	{
		gunStats.accuracy.AddMultiplicativeModifier(multiplicativeModStats.accuracy);
	}
	if (multiplicativeModStats.damage != 1)
	{
		gunStats.damage.AddMultiplicativeModifier(0);
	}
	if (multiplicativeModStats.numberOfProjectilesToShoot != 1)
	{
		gunStats.numberOfProjectilesToShoot.AddMultiplicativeModifier(this->numProjectilesMultiplier);
	}
	if (multiplicativeModStats.maxAmmo != 1)
	{
		gunStats.maxAmmo.AddMultiplicativeModifier(this->maxAmmoMultiplier);
	}

	//
	//End Multiplicative Stats
}

void UMMTurretGunMod::RemoveFromGun(AMMGunBase* gun)
{
	TGunStats& gunStats = gun->GetGunStats();

	//Multiplicative Stats
	if (multiplicativeModStats.accuracy != 1)
	{
		gunStats.accuracy.RemoveMultiplicativeModifier(multiplicativeModStats.accuracy);
	}
	if (multiplicativeModStats.damage != 1)
	{
		float x = 0;
		gunStats.damage.RemoveMultiplicativeModifier(x);
	}
	if (multiplicativeModStats.numberOfProjectilesToShoot != 1)
	{
		gunStats.numberOfProjectilesToShoot.RemoveMultiplicativeModifier(this->numProjectilesMultiplier);
	}
	if (multiplicativeModStats.maxAmmo != 1)
	{
		gunStats.maxAmmo.RemoveMultiplicativeModifier(this->maxAmmoMultiplier);
	}
	//End Multiplicative Stats
}