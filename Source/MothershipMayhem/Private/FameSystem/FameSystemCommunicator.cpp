// Fill out your copyright notice in the Description page of Project Settings.


#include "FameSystem/FameSystemCommunicator.h"
#include "Enemy/EnemyFactory.h"

// Sets default values
AFameSystemCommunicator::AFameSystemCommunicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFameSystemCommunicator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFameSystemCommunicator::SetRankScaling(float currentRank, float maxRank)
{
	EnemyFactory::SetFameScaling(currentRank, maxRank);
}

