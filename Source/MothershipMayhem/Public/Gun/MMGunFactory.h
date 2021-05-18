// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MMGunFactory.generated.h"

class AMMGunBase;
class UMMGunDataAsset;
/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API UMMGunFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//Creates the gun with name or index
	UFUNCTION(BlueprintCallable) static AMMGunBase* CreateGunWithName(FString name, UWorld* const world);
	UFUNCTION(BlueprintCallable) static AMMGunBase* CreateGunWithIndex(int index, UWorld* const world);

	//Instantiate gun object to world
	UFUNCTION(BlueprintCallable) static AMMGunBase* SpawnGun(UMMGunDataAsset* gunData, UWorld* const world);

};
