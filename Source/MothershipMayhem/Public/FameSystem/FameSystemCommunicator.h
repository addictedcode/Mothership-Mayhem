// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FameSystemCommunicator.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API AFameSystemCommunicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFameSystemCommunicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void GainFame(int increase);
	UFUNCTION(BlueprintCallable)
		bool CanRankUp();
	UFUNCTION(BlueprintCallable)
		void RankUp();

	UFUNCTION(BlueprintCallable)
		float GetCurrentRank();
	UFUNCTION(BlueprintCallable)
		float GetMaxRank();

	UFUNCTION(BlueprintCallable)
		void ResetRank();
	UFUNCTION(BlueprintCallable)
		void SetRank(int rank, int points);
};
