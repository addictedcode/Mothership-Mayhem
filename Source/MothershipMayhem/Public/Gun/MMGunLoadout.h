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

	void OnPrimaryShootPressed();
	void OnPrimaryShootReleased();
	void OnSwapWheel(float value);
	void OnReload();
	void ChangeGun(class AMMGunBase* newGun, int index);
	UFUNCTION(BlueprintCallable)
		TArray<AMMGunBase*> getGuns();

	UFUNCTION(BlueprintCallable)
		void UpdateGunStats(int index, 
							int attack,
							float fireRate, 
							float reloadSpeed, 
							int magazineSize, 
							float accuracy);

	//object pool for the bullets
	AActor** bulletPool;

protected:
	/**Gun */
	
	class AMMGunBase* gun[3];
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int currentGunIndex;
};
