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
UENUM(BlueprintType)
enum class MMChallengeType : uint8
{
	Survival = 0 UMETA(DisplayName = "Survival"),
	Defense = 1 UMETA(DisplayName = "Defense"),
	Extermination = 2 UMETA(DisplayName = "Extermination"),
};

UCLASS(BlueprintType)
class MOTHERSHIPMAYHEM_API UMMArenaChallenge_DataAsset : public UDataAsset
{
	GENERATED_BODY()
public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
		MMChallengeType challengeType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time Limit")
		int timeLimitSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")
		FString challengeTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Description")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawns")
		TArray<class UMMEnemyWave_DataAsset*> spawnList;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rewards")
		int money;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rewards")
		int famePoints;

};
