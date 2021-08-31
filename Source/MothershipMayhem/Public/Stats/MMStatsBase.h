// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template<typename T = float>
class MOTHERSHIPMAYHEM_API TMMStatsBase
{
public:
	TMMStatsBase() = default;
	~TMMStatsBase() = default;

protected:
	T baseValue; //base value to be added / times to final value
	T finalValue; //total value of the base value added / times with the modifiers

	TArray<T> additionModifiers; //Modifiers to be added to the baseValue
	TArray<float> multiplicativeModifiers; //Modifiers to be multiply to the baseValue

public:
	//Get / Set variables
	T GetFinalValue() const { return finalValue; };

	T GetBaseValue() const { return baseValue; };
	void SetBaseValue(T& newValue) { baseValue = newValue; UpdateFinalValue(); };

	void AddAdditionModifier(T newValue) { additionModifiers.Add(newValue); UpdateFinalValue(); };
	void RemoveAdditionModifier(T& value) { additionModifiers.RemoveSingleSwap(value); UpdateFinalValue(); };
	
	void AddMultiplicativeModifier(T newValue) { multiplicativeModifiers.Add(newValue); UpdateFinalValue(); };
	void RemoveMultiplicativeModifier(T& value) { multiplicativeModifiers.RemoveSingleSwap(value); UpdateFinalValue(); };

	void RemoveAllMultiplicativeModifiers() { multiplicativeModifiers.Empty(); UpdateFinalValue(); }
	void RemoveAllAdditionModifiers() { additionModifiers.Empty(); UpdateFinalValue(); }
protected:
	//Add the additionModifiers first to the baseValue then multiply with multiplicativeModifiers, then set finalValue with the result
	void UpdateFinalValue() {
		float tempValue = (float)baseValue;

		for (T value : additionModifiers)
		{
			tempValue += value;
		}

		for (float value : multiplicativeModifiers)
		{
			tempValue *= value;
		}

		finalValue = (T)tempValue;
	}
};
