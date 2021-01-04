// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/MMGunDataAsset.h"

 FPrimaryAssetId UMMGunDataAsset::GetPrimaryAssetId() const
{

	return FPrimaryAssetId(ItemType, GetFName());
}
