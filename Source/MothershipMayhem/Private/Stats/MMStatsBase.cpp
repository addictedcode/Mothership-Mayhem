// Fill out your copyright notice in the Description page of Project Settings.


#include "Stats/MMStatsBase.h"

TMMStatsBase::TMMStatsBase()
{
}

TMMStatsBase::~TMMStatsBase()
{
}

void TMMStatsBase::UpdateFinalValue()
{
	float tempValue = baseValue;

	for (float value : additionModifiers)
	{
		tempValue += value;
	}

	for (float value : multiplicativeModifiers)
	{
		tempValue *= value;
	}

	finalValue = tempValue;
}
