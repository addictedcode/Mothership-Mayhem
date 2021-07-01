// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod/MMVacuumGun.h"
#include "Gun/MMGunBase.h"

#include "Mod/MMModFactory.h"

UMMModBase* UMMVacuumGun::InitializeMod(TSubclassOf<class AMMProjectileBase> newProjectileClass)
{
	name = "Vacuum Gun";
	projectileClass = newProjectileClass;
	return this;
}

void UMMVacuumGun::AddToGun(AMMGunBase* gun)
{
	gun->SetVacuumMod(true);
}

void UMMVacuumGun::RemoveFromGun(AMMGunBase* gun)
{
	gun->SetVacuumMod(false);
}