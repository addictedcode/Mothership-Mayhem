// Fill out your copyright notice in the Description page of Project Settings.


#include "Mod/MMModFactory.h"
#include "Engine/AssetManager.h"
#include "Mod/MMModDataAsset.h"
#include "Mod/MMModProjectileOnHitEffect.h"
#include "Projectiles/MMProjectileOnHitStatusEffect.h"


UMMModBase* UMMModFactory::CreateModWithName(FString name) 
{
    //Get mod list from asset manager
    UAssetManager& assetManager = UAssetManager::Get();
    TArray<FAssetData> modList;
    assetManager.GetPrimaryAssetDataList("Mods", modList);

    //find mod data with name
    UMMModDataAsset* foundModData = NULL;
    for (FAssetData data : modList)
    {
        UMMModDataAsset* modData = Cast<UMMModDataAsset>(data.GetAsset());
        if (modData->name == name) {
            foundModData = modData;
            break;
        }
    }
	
    return InstantiateMod(foundModData);
}

UMMModBase* UMMModFactory::CreateModWithIndex(int index)
{
    //Get gun list from asset manager
    UAssetManager& assetManager = UAssetManager::Get();
    TArray<FAssetData> modList;
    assetManager.GetPrimaryAssetDataList("Mods", modList);

    //if index outside of modlist, return null
    if (index < 0 || index >= modList.Num())
    {
        return NULL;
    }

    UMMModDataAsset* modData = Cast<UMMModDataAsset>(modList[index].GetAsset());

    return InstantiateMod(modData);
}

UMMModBase* UMMModFactory::InstantiateMod(UMMModDataAsset* modData)
{
    FModStats newAdditiveStats;
    newAdditiveStats.projectileSpeed = modData->add_projectileSpeed;
    newAdditiveStats.accuracy = modData->add_accuracy;
    newAdditiveStats.damage = modData->add_damage;
    newAdditiveStats.fireRate = modData->add_fireRate;
    newAdditiveStats.maxAmmo = modData->add_maxAmmo;
    newAdditiveStats.numberOfProjectilesToShoot = modData->add_numberOfProjectilesToShoot;
    newAdditiveStats.projectileGravityScale = modData->add_projectileGravityScale;
    newAdditiveStats.reloadTime = modData->add_reloadTime;

    FModStats newMultiplicativeStats;
    newMultiplicativeStats.projectileSpeed = modData->multiply_projectileSpeed;
    newMultiplicativeStats.accuracy = modData->multiply_accuracy;
    newMultiplicativeStats.damage = modData->multiply_damage;
    newMultiplicativeStats.fireRate = modData->multiply_fireRate;
    newMultiplicativeStats.maxAmmo = modData->multiply_maxAmmo;
    newMultiplicativeStats.numberOfProjectilesToShoot = modData->multiply_numberOfProjectilesToShoot;
    newMultiplicativeStats.projectileGravityScale = modData->multiply_projectileGravityScale;
    newMultiplicativeStats.reloadTime = modData->multiply_reloadTime;

    auto& type = modData->modType;
	switch (type)
	{
    case MMModType::Basic: return InstantiateModBasic(modData, newAdditiveStats, newMultiplicativeStats); break;
    case MMModType::ProjectileEffect: return InstantiateModProjectileOnHitEffect(modData, newAdditiveStats, newMultiplicativeStats); break;
    default: return InstantiateModBasic(modData, newAdditiveStats, newMultiplicativeStats); break;
	}

    return nullptr;
}

UMMModBase* UMMModFactory::InstantiateModBasic(UMMModDataAsset* modData, const FModStats& newAdditiveStats,
    const FModStats& newMultiplicativeStats)
{
    UMMModBase* newMod = NewObject<UMMModBase>();
    newMod->InitializeMod(newAdditiveStats, newMultiplicativeStats, modData->projectileClass, modData->name);
    return newMod;
}

UMMModBase* UMMModFactory::InstantiateModProjectileOnHitEffect(UMMModDataAsset* modData, const FModStats& newAdditiveStats,
    const FModStats& newMultiplicativeStats)
{
    UMMModProjectileOnHitEffect* newMod = NewObject<UMMModProjectileOnHitEffect>();
    newMod->InitializeMod(newAdditiveStats, newMultiplicativeStats, modData->projectileClass, modData->name);
    auto& onHitEffectType = modData->projectileOnHitEffectType;
	switch(onHitEffectType)
	{
    case MMProjectOnHitEffectType::StatusEffect:
        auto* statusEffect = NewObject<UMMProjectileOnHitStatusEffect>();
        statusEffect->statusEffect = modData->projectileStatusEffect;
        newMod->projectileOnHitEffect = statusEffect;
        break;
	}
    return newMod;
}

