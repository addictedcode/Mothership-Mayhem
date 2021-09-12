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

	T m_min = 0; //min value for finalValue; if 0 and equals to m_max \ m_min, no liumit
	T m_max = 0; //max value for finalValue; if m_max < m_min, no max

	TArray<T> additionModifiers; //Modifiers to be added to the baseValue
	TArray<float> multiplicativeModifiers; //Modifiers to be multiply to the baseValue

public:
	//Get / Set variables
	T GetFinalValue() const { return finalValue; };

	T GetBaseValue() const { return baseValue; };
	void SetBaseValue(T& newValue) { baseValue = newValue; UpdateFinalValue(); };

	void AddAdditionModifier(T newValue) { additionModifiers.Add(newValue); UpdateFinalValue(); };
	void RemoveAdditionModifier(const T& value) { additionModifiers.RemoveSingleSwap(value); UpdateFinalValue(); };
	
	void AddMultiplicativeModifier(float newValue) { multiplicativeModifiers.Add(newValue); UpdateFinalValue(); };
	void RemoveMultiplicativeModifier(const float& value) { multiplicativeModifiers.RemoveSingleSwap(value); UpdateFinalValue(); };

	void RemoveAllMultiplicativeModifiers() { multiplicativeModifiers.Empty(); UpdateFinalValue(); }
	void RemoveAllAdditionModifiers() { additionModifiers.Empty(); UpdateFinalValue(); }

	void SetMinMax(T min, T max) { m_min = min; m_max = max; }
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

		if (!(m_min == m_max == 0)) {
			tempValue = (float)std::max(m_min, (T)tempValue);
			if (m_max > m_min)
				tempValue = (float)std::min(m_max, (T)tempValue);
		}
		
		finalValue = (T)tempValue;
	}
};
