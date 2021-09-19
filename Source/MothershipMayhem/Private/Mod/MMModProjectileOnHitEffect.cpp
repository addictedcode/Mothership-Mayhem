// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod/MMModProjectileOnHitEffect.h"
#include "Projectiles/MMProjectileOnHitEffect.h"
#include "Gun/MMGunBase.h"

void UMMModProjectileOnHitEffect::AddToGun(AMMGunBase* gun)
{
	UMMModBase::AddToGun(gun);
	gun->projectileOnHitEffects.Add(projectileOnHitEffect);
}

void UMMModProjectileOnHitEffect::RemoveFromGun(AMMGunBase* gun)
{
	UMMModBase::RemoveFromGun(gun);
	gun->projectileOnHitEffects.Remove(projectileOnHitEffect);
}
