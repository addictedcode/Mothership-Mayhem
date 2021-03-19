// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

namespace FameManager
{
	void GainFame(int increase);
	bool CanRankUp();
	void RankUp();

	float GetCurrentRank();
	float GetMaxRank();

	void ResetRank();
	void SetRank(int rank, int points);
}
