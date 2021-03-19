// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AAICharacter;
class AEnemyController;

namespace EnemyFactory
{
	void InitializeEnemy(FString name, AAICharacter* character, AEnemyController* controller);
	void InitializeEnemy(int index, AAICharacter* character, AEnemyController* controller);
}