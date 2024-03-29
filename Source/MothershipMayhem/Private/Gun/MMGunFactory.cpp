// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/MMGunFactory.h"
#include "Engine/AssetManager.h"
#include "Gun/MMGunBase.h"
#include "Gun/MMGunDataAsset.h"

//Spawns the gun actor to world with the name found in the asset manager type "Guns"

AMMGunBase* UMMGunFactory::CreateGunWithName(FString name, UWorld* const world)
{
    //Get gun list from asset manager
    UAssetManager& assetManager = UAssetManager::Get();
    TArray<FAssetData> gunList;
    assetManager.GetPrimaryAssetDataList("Guns", gunList);

    //find gun data with name
    UMMGunDataAsset* foundGunData = NULL;
    for (FAssetData data : gunList)
    {
        UMMGunDataAsset* gunData = Cast<UMMGunDataAsset>(data.GetAsset());
        if (gunData->name == name) {
            foundGunData = gunData;
            break;
        }
    }

    //Spawn gun
    return UMMGunFactory::SpawnGun(foundGunData, world);
}

//Spawns the gun actor to world with the index found the in asset manager type "Guns"
AMMGunBase* UMMGunFactory::CreateGunWithIndex(int index, UWorld* const world)
{
    //Get gun list from asset manager
    UAssetManager& assetManager = UAssetManager::Get();
    TArray<FAssetData> gunList;
    assetManager.GetPrimaryAssetDataList("Guns", gunList);

    //if index outside of gunlist, return null
    if (index < 0 || index >= gunList.Num())
    {
        return NULL;
    }

    UMMGunDataAsset* gunData = Cast<UMMGunDataAsset>(gunList[index].GetAsset());

    //Spawn Gun
    return UMMGunFactory::SpawnGun(gunData, world);

}



AMMGunBase* UMMGunFactory::SpawnGun(UMMGunDataAsset* gunData, UWorld* const world)
{
    if (world != NULL || gunData != NULL) {
        /*AActor* newObject = world->SpawnActor<AMMGunBase>();
        AMMGunBase* newGun = Cast<AMMGunBase>(newObject);*/

        AActor* newObject = world->SpawnActor<AActor>(gunData->gunBP);
        AMMGunBase* newGun = Cast<AMMGunBase>(newObject);

        //setting attached objects/components

        newGun->SetProjectile(gunData->projectileClass);
        newGun->SetDefaultProjectile(gunData->projectileClass);
        newGun->SetMuzzleFlash(gunData->muzzleFlashFX);

    	//SFX
        newGun->m_shoot_sfx = gunData->m_gun_shoot_sfx;
        newGun->m_default_shoot_sfx = gunData->m_gun_shoot_sfx;
        newGun->m_hit_sfx = gunData->m_gun_hit_sfx;
        newGun->m_default_hit_sfx = gunData->m_gun_hit_sfx;
        newGun->m_reload_sfx = gunData->m_gun_reload_sfx;

        //set gun stats
        TGunStats& gunStats = newGun->GetGunStats();
        gunStats.fireRate.SetBaseValue(gunData->fireRate);
        gunStats.fireRate.SetMinMax(0.01f, 0.f);
        gunStats.maxAmmo.SetBaseValue(gunData->maxAmmo);
        gunStats.maxAmmo.SetMinMax(0, -1);
        gunStats.currentAmmo = gunStats.maxAmmo.GetFinalValue();
        gunStats.reloadTime.SetBaseValue(gunData->reloadTime);
        gunStats.reloadTime.SetMinMax(0.01f, 0.f);
        gunStats.isAutomatic = gunData->isAutomatic;
        gunStats.accuracy.SetBaseValue(gunData->accuracy);
        gunStats.accuracy.SetMinMax(0.f, 100.f);
        gunStats.numberOfProjectilesToShoot.SetBaseValue(gunData->numberOfProjectilesToShoot);
        gunStats.numberOfProjectilesToShoot.SetMinMax(1, 0);
        gunStats.damage.SetBaseValue(gunData->damage);
        gunStats.projectileSpeed.SetBaseValue(gunData->projectileSpeed);
        gunStats.isBouncingProjectile = gunData->isBouncingProjectile;
        gunStats.projectileGravityScale.SetBaseValue(gunData->projectileGravityScale);

        return newGun;
    }
    return NULL;
}