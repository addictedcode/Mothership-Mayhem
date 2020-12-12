// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/MMGunLoadout.h"
#include "Gun/MMGunBase.h"
#include "Engine/AssetManager.h"
#include "Gun/MMGunFactory.h"

// Sets default values for this component's properties
UMMGunLoadout::UMMGunLoadout()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	currentGunIndex = 0;
}


// Called when the game starts
void UMMGunLoadout::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UWorld* world = this->GetWorld();
	
	ChangeGun(GunFactory::CreateGun("Pistol", world), 0);
	ChangeGun(GunFactory::CreateGun("MachineGun", world), 1);
}

void UMMGunLoadout::OnPrimaryShootPressed()
{
	if (gun[currentGunIndex] != NULL) 
	{
		gun[currentGunIndex]->OnPrimaryShootPressed();
	}
}

void UMMGunLoadout::OnPrimaryShootReleased()
{
	if (gun[currentGunIndex] != NULL)
	{
		gun[currentGunIndex]->OnPrimaryShootReleased();
	}
}


void UMMGunLoadout::OnSwapWheel(float value)
{
	int previousGunIndex = currentGunIndex;
	
	//scroll down
	if (value < 0)
	{
		for (int i = 0; i < 3; ++i) {
			currentGunIndex--;
			if (currentGunIndex < 0)
			{
				currentGunIndex = 2;
			}
			if (gun[currentGunIndex] != NULL)
			{
				break;
			}
		}
	}
	//scroll up
	else if (value > 0)
	{
		for (int i = 0; i < 3; ++i) {
			currentGunIndex++;
			if (currentGunIndex > 2)
			{
				currentGunIndex = 0;
			}
			if (gun[currentGunIndex] != NULL)
			{
				break;
			}
		}
	}

	if (previousGunIndex == currentGunIndex)
	{
		return;
	}
	
	gun[previousGunIndex]->SetActorHiddenInGame(true);
	gun[previousGunIndex]->OnHolster();
	
	gun[currentGunIndex]->SetActorHiddenInGame(false);
	gun[currentGunIndex]->OnDraw();
}

void UMMGunLoadout::OnReload()
{
	if (gun[currentGunIndex] != NULL)
	{
		gun[currentGunIndex]->OnReload();
	}
}

void UMMGunLoadout::ChangeGun(AMMGunBase* newGun, int index)
{
	// old gun
	if (gun[index] != NULL)
	{
		gun[index]->Destroy();
		gun[index] = newGun;
	}
	else
	{
		gun[index] = newGun;
	}

	//new gun
	if (gun[index] != NULL)
	{
		gun[index]->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		if (index != currentGunIndex)
		{
			gun[index]->SetActorHiddenInGame(true);
		}
	}
}

TArray<AMMGunBase*> UMMGunLoadout::getGuns()
{
	TArray<AMMGunBase*> gunsToReturn;
	for (int i = 0; i < 3; ++i) {
		gunsToReturn.Emplace(gun[i]);
	}
	return gunsToReturn;
}








