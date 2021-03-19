// Fill out your copyright notice in the Description page of Project Settings.


#include "FameSystem/FameManager.h"

namespace FameManager
{
	int fameRank = 1;
	int maxRank = 5;
	int famePoints = 0;
	int pointsToRankUp[] = {1000, 1000, 2000, 5000};

	void GainFame(int increase)
	{
		famePoints = FMath::Clamp(famePoints + increase, 0, pointsToRankUp[fameRank - 1]);
	}

	bool CanRankUp()
	{
		if (fameRank < maxRank)
			return famePoints == pointsToRankUp[fameRank - 1];
		return false;
	}

	void RankUp()
	{
		if (CanRankUp())
		{
			fameRank++;
			famePoints = 0;
		}
	}

	float GetCurrentRank()
	{
		return fameRank;
	}

	float GetMaxRank()
	{
		return maxRank;
	}

	void ResetRank()
	{
		fameRank = 1;
		famePoints = 0;
	}

	void SetRank(int rank, int points)
	{
		fameRank = rank;
		famePoints = points;
	}
}
