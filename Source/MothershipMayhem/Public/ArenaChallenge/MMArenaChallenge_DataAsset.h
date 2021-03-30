// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy/AICharacter.h"
#include "ArenaChallenge/MMEnemyWave_DataAsset.h"
#include "MMArenaChallenge_DataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMArenaChallenge_DataAsset : public UDataAsset
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")
		FString challengeTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawns")
		TArray<class UMMEnemyWave_DataAsset*> spawnList;


};
