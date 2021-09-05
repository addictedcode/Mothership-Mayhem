// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Mod/MMModBase.h"
#include "MMModFactory.generated.h"

class UMMModDataAsset;

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMModFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) static UMMModBase* CreateModWithName(
		UPARAM(DisplayName = "Name") FString name);
	UFUNCTION(BlueprintCallable) static UMMModBase* CreateModWithIndex(
		UPARAM(DisplayName = "Index") int index);
	
	UFUNCTION(BlueprintCallable) static UMMModBase* InstantiateMod(
		UPARAM(DisplayName = "Mod Data") UMMModDataAsset* modData);

	//For Different Mods
	UFUNCTION(BlueprintCallable) static UMMModBase* InstantiateModBasic(
		UPARAM(DisplayName = "Mod Data") UMMModDataAsset* modData,
		UPARAM(DisplayName = "Additive Stats") const FModStats& newAdditiveStats,
		UPARAM(DisplayName = "Multiplicative Stats") const  FModStats& newMultiplicativeStats);
	
	UFUNCTION(BlueprintCallable) static UMMModBase* InstantiateModProjectileOnHitEffect(
		UPARAM(DisplayName = "Mod Data") UMMModDataAsset* modData,
		UPARAM(DisplayName = "Additive Stats") const FModStats& newAdditiveStats,
		UPARAM(DisplayName = "Multiplicative Stats") const FModStats& newMultiplicativeStats);

	UFUNCTION(BlueprintCallable) static UMMModBase* InstantiateModLegendary(
		UPARAM(DisplayName = "Mod Data") UMMModDataAsset* modData,
		UPARAM(DisplayName = "Additive Stats") const FModStats& newAdditiveStats,
		UPARAM(DisplayName = "Multiplicative Stats") const FModStats& newMultiplicativeStats);
};
