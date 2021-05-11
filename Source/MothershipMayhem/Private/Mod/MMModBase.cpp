// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod/MMModBase.h"
#include "Gun/MMGunBase.h"

#include "Mod/MMModFactory.h"

UMMModBase* UMMModBase::InitializeMod(FModStats newAdditiveModStats, FModStats newMultiplicativeModStats, FString newName)
{
	additiveModStats = newAdditiveModStats;
	multiplicativeModStats = newMultiplicativeModStats;
	name = newName;
	UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *name, *newName);
	return this;
}

void UMMModBase::AddToGun(AMMGunBase* gun)
{
	TGunStats& gunStats = gun->GetGunStats();
	
	//Additive Stats
	if (additiveModStats.projectileSpeed != 0) 
	{
		gunStats.projectileSpeed.AddAdditionModifier(additiveModStats.projectileSpeed);
	}
	if (additiveModStats.accuracy != 0)
	{
		gunStats.accuracy.AddAdditionModifier(additiveModStats.accuracy);
	}
	if (additiveModStats.damage != 0)
	{
		gunStats.damage.AddAdditionModifier(additiveModStats.damage);
	}
	if (additiveModStats.fireRate != 0)
	{
		gunStats.fireRate.AddAdditionModifier(additiveModStats.fireRate);
	}
	if (additiveModStats.numberOfProjectilesToShoot != 0)
	{
		gunStats.numberOfProjectilesToShoot.AddAdditionModifier(additiveModStats.numberOfProjectilesToShoot);
	}
	if (additiveModStats.projectileGravityScale != 0)
	{
		gunStats.projectileGravityScale.AddAdditionModifier(additiveModStats.projectileGravityScale);
	}
	if (additiveModStats.reloadTime != 0)
	{
		gunStats.reloadTime.AddAdditionModifier(additiveModStats.reloadTime);
	}
	if (additiveModStats.maxAmmo != 0)
	{
		gunStats.maxAmmo.AddAdditionModifier(additiveModStats.maxAmmo);
	}
	//End Additive Stats

	//Multiplicative Stats
	if (multiplicativeModStats.projectileSpeed != 1)
	{
		gunStats.projectileSpeed.AddMultiplicativeModifier(multiplicativeModStats.projectileSpeed);
	}
	if (multiplicativeModStats.accuracy != 1)
	{
		gunStats.accuracy.AddMultiplicativeModifier(multiplicativeModStats.accuracy);
	}
	if (multiplicativeModStats.damage != 1)
	{
		gunStats.damage.AddMultiplicativeModifier(multiplicativeModStats.damage);
	}
	if (multiplicativeModStats.fireRate != 1)
	{
		gunStats.fireRate.AddMultiplicativeModifier(multiplicativeModStats.fireRate);
	}
	if (multiplicativeModStats.numberOfProjectilesToShoot != 1)
	{
		gunStats.numberOfProjectilesToShoot.AddMultiplicativeModifier(multiplicativeModStats.numberOfProjectilesToShoot);
	}
	if (multiplicativeModStats.projectileGravityScale != 1)
	{
		gunStats.projectileGravityScale.AddMultiplicativeModifier(multiplicativeModStats.projectileGravityScale);
	}
	if (multiplicativeModStats.reloadTime != 1)
	{
		gunStats.reloadTime.AddMultiplicativeModifier(multiplicativeModStats.reloadTime);
	}
	if (multiplicativeModStats.maxAmmo != 1)
	{
		gunStats.maxAmmo.AddMultiplicativeModifier(multiplicativeModStats.maxAmmo);
	}
	//End Multiplicative Stats
}

void UMMModBase::RemoveFromGun(AMMGunBase* gun)
{
	TGunStats& gunStats = gun->GetGunStats();

	//Additive Stats
	if (additiveModStats.projectileSpeed != 0)
	{
		gunStats.projectileSpeed.RemoveAdditionModifier(additiveModStats.projectileSpeed);
	}
	if (additiveModStats.accuracy != 0)
	{
		gunStats.accuracy.RemoveAdditionModifier(additiveModStats.accuracy);
	}
	if (additiveModStats.damage != 0)
	{
		gunStats.damage.RemoveAdditionModifier(additiveModStats.damage);
	}
	if (additiveModStats.fireRate != 0)
	{
		gunStats.fireRate.RemoveAdditionModifier(additiveModStats.fireRate);
	}
	if (additiveModStats.numberOfProjectilesToShoot != 0)
	{
		gunStats.numberOfProjectilesToShoot.RemoveAdditionModifier(additiveModStats.numberOfProjectilesToShoot);
	}
	if (additiveModStats.projectileGravityScale != 0)
	{
		gunStats.projectileGravityScale.RemoveAdditionModifier(additiveModStats.projectileGravityScale);
	}
	if (additiveModStats.reloadTime != 0)
	{
		gunStats.reloadTime.RemoveAdditionModifier(additiveModStats.reloadTime);
	}
	if (additiveModStats.maxAmmo != 0)
	{
		gunStats.maxAmmo.RemoveAdditionModifier(additiveModStats.maxAmmo);
	}
	//End Additive Stats

	//Multiplicative Stats
	if (multiplicativeModStats.projectileSpeed != 1)
	{
		gunStats.projectileSpeed.RemoveMultiplicativeModifier(multiplicativeModStats.projectileSpeed);
	}
	if (multiplicativeModStats.accuracy != 1)
	{
		gunStats.accuracy.RemoveMultiplicativeModifier(multiplicativeModStats.accuracy);
	}
	if (multiplicativeModStats.damage != 1)
	{
		gunStats.damage.RemoveMultiplicativeModifier(multiplicativeModStats.damage);
	}
	if (multiplicativeModStats.fireRate != 1)
	{
		gunStats.fireRate.RemoveMultiplicativeModifier(multiplicativeModStats.fireRate);
	}
	if (multiplicativeModStats.numberOfProjectilesToShoot != 1)
	{
		gunStats.numberOfProjectilesToShoot.RemoveMultiplicativeModifier(multiplicativeModStats.numberOfProjectilesToShoot);
	}
	if (multiplicativeModStats.projectileGravityScale != 1)
	{
		gunStats.projectileGravityScale.RemoveMultiplicativeModifier(multiplicativeModStats.projectileGravityScale);
	}
	if (multiplicativeModStats.reloadTime != 1)
	{
		gunStats.reloadTime.RemoveMultiplicativeModifier(multiplicativeModStats.reloadTime);
	}
	if (multiplicativeModStats.maxAmmo != 1)
	{
		gunStats.maxAmmo.RemoveMultiplicativeModifier(multiplicativeModStats.maxAmmo);
	}
	//End Multiplicative Stats
}

FModStats UMMModBase::GetAdditiveModStats()
{
	return additiveModStats;
}

FModStats UMMModBase::GetMultiplicativeModStats()
{
	return multiplicativeModStats;
}
