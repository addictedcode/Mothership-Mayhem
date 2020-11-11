// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MMGunLoadout.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOTHERSHIPMAYHEM_API UMMGunLoadout : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMMGunLoadout();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void OnShoot();
	void OnSwapWheel(float value);
	void ChangeGun(class AMMGunBase* newGun, int index);
	
protected:
	/**Gun */
	class AMMGunBase* gun[3];
	int currentGunIndex;
};
