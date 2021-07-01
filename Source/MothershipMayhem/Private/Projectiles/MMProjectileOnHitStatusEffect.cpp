// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileOnHitStatusEffect.h"

void UMMProjectileOnHitStatusEffect::ApplyEffect(UEnemyStatsComponent* enemy, FVector position)
{
	enemy->ApplyStatusEffect(statusEffect);
}
