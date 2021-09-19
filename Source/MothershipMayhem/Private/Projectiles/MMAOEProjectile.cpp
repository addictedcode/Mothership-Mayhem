// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MMAOEProjectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enemy/AICharacter.h"
#include "Enemy/EnemyStatsComponent.h"

void AMMAOEProjectile::onHitSpecialEffect(FHitResult hit)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> ignoreActors;
	TArray<AActor*> outActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), this->GetActorLocation(), this->radius, traceObjectTypes, AAICharacter::StaticClass(), ignoreActors, outActors);

	for (int i = 0; i < outActors.Num(); i++) {
		AAICharacter* enemy = Cast<AAICharacter>(outActors[i]);
		if (enemy != nullptr)
			enemy->getEnemyStats()->TakeDamage(areaOfEffectDamage);
	}
}