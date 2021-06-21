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
	
	ChangeGun(UMMGunFactory::CreateGunWithName("Pistol", world), 0);
	ChangeGun(UMMGunFactory::CreateGunWithName("MachineGun", world), 1);
	ChangeGun(UMMGunFactory::CreateGunWithName("Shotgun", world), 2);
}

void UMMGunLoadout::OnPrimaryShootPressed()
{
	if (gunList.IsValidIndex(currentGunIndex)) 
	{
		gunList[currentGunIndex]->OnPrimaryShootPressed();
	}
}

void UMMGunLoadout::OnPrimaryShootReleased()
{
	if (gunList.IsValidIndex(currentGunIndex))
	{
		gunList[currentGunIndex]->OnPrimaryShootReleased();
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
			if (gunList.IsValidIndex(currentGunIndex))
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
			if (gunList.IsValidIndex(currentGunIndex))
			{
				break;
			}
		}
	}

	if (previousGunIndex == currentGunIndex)
	{
		return;
	}
	
	gunList[previousGunIndex]->SetActorHiddenInGame(true);
	gunList[previousGunIndex]->OnHolster();
	
	gunList[currentGunIndex]->SetActorHiddenInGame(false);
	gunList[currentGunIndex]->OnDraw();
}

void UMMGunLoadout::OnReload()
{
	if (gunList.IsValidIndex(currentGunIndex))
	{
		gunList[currentGunIndex]->OnReload();
	}
}

void UMMGunLoadout::ChangeGun(AMMGunBase* newGun, int index)
{
	if (this->bulletPool != nullptr) {
		newGun->bulletPool = this->bulletPool;
	}
	// old gun
	if (gunList.IsValidIndex(index))
	{
		gunList[index]->Destroy();
		gunList.Insert(newGun, index);
	}
	else
	{
		gunList.Insert(newGun, index);
	}

	//new gun
	if (gunList.IsValidIndex(index))
	{
		gunList[index]->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		if (index != currentGunIndex)
		{
			gunList[index]->SetActorHiddenInGame(true);
		}
	}
}

TArray<AMMGunBase*> UMMGunLoadout::getGuns()
{
	return gunList;
}

void UMMGunLoadout::UpdateGunStats(int index, int attack, float fireRate, float reloadSpeed, int magazineSize, float accuracy) {
	if (gunList.IsValidIndex(index))
	{
		gunList[index]->UpdateStats(index, attack, fireRate, reloadSpeed, magazineSize, accuracy);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Gun"));
	}
}







