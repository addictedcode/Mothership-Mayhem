// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MOTHERSHIPMAYHEM_API TMMStatsBase
{
public:
	TMMStatsBase();
	~TMMStatsBase();

protected:
	float baseValue; //base value to be added / times to final value
	float finalValue; //total value of the base value added / times with the modifiers

	TArray<float> addictionModifiers; //Modifiers to be added to the baseValue
	TArray<float> multiplicativeModifiers; //Modifiers to be multiply to the baseValue

public:
	//Get / Set variables
	float GetFinalValue() const { return finalValue; };

	float GetBaseValue() const { return baseValue; };
	void SetBaseValue(float& newValue) { baseValue = newValue; UpdateFinalValue(); };

	void AddAdditionModifier(float newValue) { addictionModifiers.Add(newValue); UpdateFinalValue(); };
	void RemoveAddictionModifier(float& value) { addictionModifiers.RemoveSingleSwap(value); UpdateFinalValue(); };
	
	void AddMultiplicativeModifier(float newValue) { multiplicativeModifiers.Add(newValue); UpdateFinalValue(); };
	void RemoveMultiplicativeModifier(float& value) { multiplicativeModifiers.RemoveSingleSwap(value); UpdateFinalValue(); };

	void RemoveAllMultiplicativeModifiers() { multiplicativeModifiers.Empty(); UpdateFinalValue(); }
	void RemoveAllAdditionModifiers() { addictionModifiers.Empty(); UpdateFinalValue(); }
protected:
	//Add the additionModifiers first to the baseValue then multiply with multiplicativeModifiers, then set finalValue with the result
	void UpdateFinalValue();
};
