// Fill out your copyright notice in the Description page of Project Settings.


#include "FameSystem/FameSystemCommunicator.h"
#include "FameSystem/FameManager.h"

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

void AFameSystemCommunicator::GainFame(int increase)
{
	FameManager::GainFame(increase);
}

bool AFameSystemCommunicator::CanRankUp()
{
	return FameManager::CanRankUp();
}

void AFameSystemCommunicator::RankUp()
{
	FameManager::RankUp();
}

float AFameSystemCommunicator::GetCurrentRank()
{
	return FameManager::GetCurrentRank();
}

float AFameSystemCommunicator::GetMaxRank()
{
	return FameManager::GetMaxRank();
}

void AFameSystemCommunicator::ResetRank()
{
	FameManager::ResetRank();
}

void AFameSystemCommunicator::SetRank(int rank, int points)
{
	FameManager::SetRank(rank, points);
}

