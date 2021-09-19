// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod/MMModBase.h"
#include "Gun/MMGunBase.h"
#include "Mod/MMModFactory.h"

UMMModBase* UMMModBase::InitializeMod(FModStats newAdditiveModStats, 
									FModStats newMultiplicativeModStats,
									TSubclassOf<class AMMProjectileBase> newProjectileClass,
									FString newName)
{
	additiveModStats = newAdditiveModStats;
	multiplicativeModStats = newMultiplicativeModStats;
	name = newName;
	projectileClass = newProjectileClass;
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

	if (m_shoot_sfx)
		gun->m_shoot_sfx = m_shoot_sfx;
	if (m_hit_sfx)
		gun->m_hit_sfx = m_hit_sfx;
	//
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
		gunStats.numberOfProjectilesToShoot.RemoveAdditionModifier((int)additiveModStats.numberOfProjectilesToShoot);
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
		gunStats.maxAmmo.RemoveAdditionModifier((int)additiveModStats.maxAmmo);
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

	gun->m_shoot_sfx = gun->m_default_shoot_sfx;
	gun->m_hit_sfx = gun->m_default_hit_sfx;
}

FModStats UMMModBase::GetAdditiveModStats()
{
	return additiveModStats;
}

FModStats UMMModBase::GetMultiplicativeModStats()
{
	return multiplicativeModStats;
}

UMMModBase* UMMModBase::UpdateMuzzleFlash(UNiagaraSystem* newMuzzleFlash)
{
	this->muzzleFlashFX = newMuzzleFlash;
	return this;
}

TArray<FString> UMMModBase::getRelevantStatNames()
{
	TArray<FString> names;
	if (additiveModStats.damage != 0 || multiplicativeModStats.damage != 1)
	{
		names.Add(TEXT("Damage"));
	}
	if (additiveModStats.fireRate != 0 || multiplicativeModStats.fireRate != 1)
	{
		names.Add(TEXT("Fire Rate"));
	}
	if (additiveModStats.reloadTime != 0 || multiplicativeModStats.projectileGravityScale != 1)
	{
		names.Add(TEXT("Reload Speed"));
	}
	if (additiveModStats.maxAmmo != 0 || multiplicativeModStats.reloadTime != 1)
	{
		names.Add(TEXT("Mag Size"));
	}
	if (additiveModStats.accuracy != 0 || multiplicativeModStats.accuracy != 1)
	{
		names.Add(TEXT("Accuracy"));
	}

	if (additiveModStats.projectileSpeed != 0 || multiplicativeModStats.projectileSpeed != 1)
	{
		names.Add(TEXT("Projectile Speed"));
	}
	if (additiveModStats.numberOfProjectilesToShoot != 0 || multiplicativeModStats.numberOfProjectilesToShoot != 1)
	{
		names.Add(TEXT("Projectile Count"));
	}
	if (additiveModStats.projectileGravityScale != 0 || multiplicativeModStats.projectileGravityScale != 1)
	{
		names.Add(TEXT("Gravity Scale"));
	}
	
	return names;
}

TArray<float> UMMModBase::getRelevantAdditiveStats() 
{

	TArray<FString> names = this->getRelevantStatNames();

	TArray<float> addStats;

	for (int32 Index = 0; Index != names.Num(); ++Index)
	{
		if (names[Index] == TEXT("Damage"))
		{
			addStats.Add(additiveModStats.damage);
		}
		if (names[Index] == TEXT("Fire Rate"))
		{
			addStats.Add(additiveModStats.fireRate);
		}
		if (names[Index] == TEXT("Reload Speed"))
		{
			addStats.Add(additiveModStats.reloadTime);
		}
		if (names[Index] == TEXT("Mag Size"))
		{
			addStats.Add(additiveModStats.maxAmmo);
		}
		if (names[Index] == TEXT("Accuracy"))
		{
			addStats.Add(additiveModStats.accuracy);
		}

		if (names[Index] == TEXT("Projectile Speed"))
		{
			addStats.Add(additiveModStats.projectileSpeed);
		}
		if (names[Index] == TEXT("Projectile Count"))
		{
			addStats.Add(additiveModStats.numberOfProjectilesToShoot);
		}
		if (names[Index] == TEXT("Gravity Scale"))
		{
			addStats.Add(additiveModStats.projectileGravityScale);
		}
	}

	return addStats;
}

TArray<float> UMMModBase::getRelevantMultiplicativeStats() 
{
	TArray<float> multStats;

	TArray<FString> names = this->getRelevantStatNames();


	for (int32 Index = 0; Index != names.Num(); ++Index)
	{
		if (names[Index] == TEXT("Damage"))
		{
			multStats.Add(multiplicativeModStats.damage);
		}
		if (names[Index] == TEXT("Fire Rate"))
		{
			multStats.Add(multiplicativeModStats.fireRate);
		}
		if (names[Index] == TEXT("Reload Speed"))
		{
			multStats.Add(multiplicativeModStats.reloadTime);
		}
		if (names[Index] == TEXT("Mag Size"))
		{
			multStats.Add(multiplicativeModStats.maxAmmo);
		}
		if (names[Index] == TEXT("Accuracy"))
		{
			multStats.Add(multiplicativeModStats.accuracy);
		}

		if (names[Index] == TEXT("Projectile Speed"))
		{
			multStats.Add(multiplicativeModStats.projectileSpeed);
		}
		if (names[Index] == TEXT("Projectile Count"))
		{
			multStats.Add(multiplicativeModStats.numberOfProjectilesToShoot);
		}
		if (names[Index] == TEXT("Gravity Scale"))
		{
			multStats.Add(multiplicativeModStats.projectileGravityScale);
		}
	}

	return multStats;
}
