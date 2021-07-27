// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileTurretMaker.h"
#include "Character/TurretGun.h"

void AMMProjectileTurretMaker::onHitSpecialEffect()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FRotator rot;

	ATurretGun* SpawnedActorRef = GetWorld()->SpawnActor<ATurretGun>(turretClass, this->GetActorLocation() , rot, ActorSpawnParams);
	SpawnedActorRef->bulletPool = this->parentPool;
}
