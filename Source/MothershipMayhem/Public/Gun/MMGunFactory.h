// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AMMGunBase;
class UMMGunDataAsset;

namespace GunFactory
{
	//Creates the gun with name or index
	AMMGunBase* CreateGun(FString name, UWorld* const world);
	AMMGunBase* CreateGun(int index, UWorld* const world);

	//Instantiate gun object to world
	AMMGunBase* SpawnGun(UMMGunDataAsset* gunData, UWorld* const world);
}