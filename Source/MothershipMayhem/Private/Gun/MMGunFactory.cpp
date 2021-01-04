// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/MMGunFactory.h"
#include "Engine/AssetManager.h"
#include "Gun/MMGunBase.h"
#include "Gun/MMGunDataAsset.h"

namespace GunFactory
{
    //Spawns the gun actor to world with the name found in the asset manager type "Guns"
    AMMGunBase* CreateGun(FString name, UWorld* const world)
    {
        //Get gun list from asset manager
        UAssetManager& assetManager = UAssetManager::Get();

        assetManager.LoadPrimaryAssetsWithType("Guns");

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
        UE_LOG(LogTemp, Warning, TEXT("LENGTH: %d"), gunList.Num());

        //Spawn gun
        return SpawnGun(foundGunData, world);
    }

    //Spawns the gun actor to world with the index found the in asset manager type "Guns"
    AMMGunBase* CreateGun(int index, UWorld* const world)
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
        return SpawnGun(gunData, world);

    }

    //Instantiate gun object to world
    AMMGunBase* SpawnGun(UMMGunDataAsset* gunData, UWorld* const world)
    {
        if (world != NULL && gunData != NULL) {
            AActor* newObject = world->SpawnActor<AMMGunBase>();
            AMMGunBase* newGun = Cast<AMMGunBase>(newObject);

            //set gun stats
                
            newGun->SetMesh(gunData->gunMesh);
            newGun->SetProjectile(gunData->projectileClass);

            TGunStats& gunStats = newGun->GetGunStats();
            gunStats.fireRate.SetBaseValue(gunData->fireRate);
            gunStats.maxAmmo.SetBaseValue(gunData->maxAmmo);
            gunStats.currentAmmo = gunStats.maxAmmo.GetFinalValue();
            gunStats.reloadTime.SetBaseValue(gunData->reloadTime);
            gunStats.isAutomatic = gunData->isAutomatic;
            gunStats.accuracy.SetBaseValue(gunData->accuracy);
            gunStats.numberOfProjectilesToShoot.SetBaseValue(gunData->numberOfProjectilesToShoot);

            return newGun;
        }
        return NULL;
    }


}