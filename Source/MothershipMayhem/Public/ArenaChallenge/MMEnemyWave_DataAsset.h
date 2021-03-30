// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MMEnemyWave_DataAsset.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API UMMEnemyWave_DataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawns")
		TArray<TSubclassOf<class AAICharacter>> spawnList;
};
