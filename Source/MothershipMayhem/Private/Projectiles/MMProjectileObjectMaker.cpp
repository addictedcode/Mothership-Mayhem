// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMProjectileObjectMaker.h"
#include "Character/TurretGun.h"
#include "Kismet/KismetMathLibrary.h"

void AMMProjectileObjectMaker::onHitSpecialEffect(FHitResult hit)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FRotator rot;

	if (sticksToSurface)
		rot = UKismetMathLibrary::MakeRotFromZ(hit.ImpactNormal);
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(actorBP, this->GetActorLocation() , rot, ActorSpawnParams);
	if (needsProjectilePool) {
		if (Cast<ATurretGun>(SpawnedActorRef) != nullptr)
			Cast<ATurretGun>(SpawnedActorRef)->bulletPool = this->parentPool;
	}
}
