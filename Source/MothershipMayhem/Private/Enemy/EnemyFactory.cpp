// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyFactory.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyStatsComponent.h"
#include "Enemy/EnemyController.h"
#include "Engine/AssetManager.h"
#include "Enemy/EnemyDataAsset.h"
#include "FameSystem/FameManager.h"

namespace EnemyFactory
{	
	void InitializeEnemy(FString name, AAICharacter* character, AEnemyController* controller)
	{
        UAssetManager& assetManager = UAssetManager::Get();
        TArray<FAssetData> enemyList;
        assetManager.GetPrimaryAssetDataList("Enemies", enemyList);

        
        //find enemy data with name
        for (FAssetData data : enemyList)
        {
            UEnemyDataAsset* enemyData = Cast<UEnemyDataAsset>(data.GetAsset());
            if (enemyData) {
                if (enemyData->name == name) {
                    character->projectileClass = enemyData->projectileClass;

                    float fameScaling = (FameManager::GetCurrentRank() - 1) / (FameManager::GetMaxRank() - 1);
                	
                    character->enemyStats->SetMaxHP(FMath::Lerp(enemyData->MaxHP, enemyData->MaxFameMaxHP, fameScaling));
                    character->UpdateReloadTime(FMath::Lerp(enemyData->SecPerShot, enemyData->MaxFameSecPerShot, fameScaling));
                    character->UpdateProjectileStats(FMath::Lerp(enemyData->AttackDamage, enemyData->MaxFameAttackDamage, fameScaling),
                        enemyData->projectileSpeed,
                        enemyData->isBouncingProjectile, enemyData->projectileGravityScale);

                    controller->UpdateAttackRange(FMath::Lerp(enemyData->AttackRange, enemyData->MaxFameAttackRange, fameScaling));
                    controller->UpdateRunSpeed(FMath::Lerp(enemyData->RunSpeed, enemyData->MaxFameRunSpeed, fameScaling));
                    controller->UpdateWalkSpeed(FMath::Lerp(enemyData->WalkSpeed, enemyData->MaxFameWalkSpeed, fameScaling));
                    return;
                }
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("No enemy data with name %s"), *name);
	}

    void InitializeEnemy(int index, AAICharacter* character, AEnemyController* controller)
    {
        UAssetManager& assetManager = UAssetManager::Get();
        TArray<FAssetData> enemyList;
        assetManager.GetPrimaryAssetDataList("Enemies", enemyList);

        if (index < 0 || index >= enemyList.Num()) {
            UE_LOG(LogTemp, Warning, TEXT("Index exceeds EnemyData list"));
            return;
        }

        //find enemy data with name
        UEnemyDataAsset* enemyData = Cast<UEnemyDataAsset>(enemyList[index].GetAsset());

        if (enemyData) {
            character->projectileClass = enemyData->projectileClass;

            character->enemyStats->SetMaxHP(enemyData->MaxHP);
            character->UpdateReloadTime(enemyData->SecPerShot);
            character->UpdateProjectileStats(enemyData->AttackDamage, enemyData->projectileSpeed,
                enemyData->isBouncingProjectile, enemyData->projectileGravityScale);

            controller->UpdateAttackRange(enemyData->AttackRange);
            controller->UpdateRunSpeed(enemyData->RunSpeed);
            controller->UpdateWalkSpeed(enemyData->WalkSpeed);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("EnemyData does not exist"));
        }
    }
}