// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MM_ProjectileEffectBase.h"

// Sets default values for this component's properties
UMM_ProjectileEffectBase::UMM_ProjectileEffectBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMM_ProjectileEffectBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMM_ProjectileEffectBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

