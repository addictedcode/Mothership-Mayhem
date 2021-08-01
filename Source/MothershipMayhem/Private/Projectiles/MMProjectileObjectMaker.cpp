// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileObjectMaker.h"
#include "Character/TurretGun.h"

void AMMProjectileObjectMaker::onHitSpecialEffect()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FRotator rot;

	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(actorBP, this->GetActorLocation() , rot, ActorSpawnParams);
	if (needsProjectilePool) {
		if (Cast<ATurretGun>(SpawnedActorRef) != nullptr)
			Cast<ATurretGun>(SpawnedActorRef)->bulletPool = this->parentPool;
	}
}
