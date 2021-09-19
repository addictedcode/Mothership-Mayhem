// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileOnHitSpawnEffect.h"

void UMMProjectileOnHitSpawnEffect::ApplyEffect(UWorld* world, const FHitResult& Hit)
{
	if (m_Spawn_Class == nullptr) return;

	const FRotator SpawnRotation = Hit.ImpactNormal.Rotation();
	const FVector SpawnLocation = Hit.ImpactPoint;

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	world->SpawnActor<AActor>(m_Spawn_Class, SpawnLocation, SpawnRotation, ActorSpawnParams);
}
