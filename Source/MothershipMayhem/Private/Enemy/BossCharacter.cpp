// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BossCharacter.h"
#include "Enemy/EnemyController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MMCharacterBase.h"

ABossCharacter::ABossCharacter() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->timeToReload = 5.0f;
	Cast<AEnemyController>(this->GetController())->UpdateAttackRange(INT_MAX);
}

void ABossCharacter::SelectMoveIndex(int index, AActor* target) {
	if (this->currentReloadTime >= this->timeToReload && !this->isStunned && !this->IsHidden() && this->currentState == BossStates::Idle) {
		this->currentReloadTime = 0;
		UWorld* const world = this->GetWorld();
		if (world == NULL)
		{
			return;
		}
		this->isImmuneToKnockback = true;
		switch (index)
		{
		case 0:
			ChargeTarget(target);
			break;
		case 1:
			JumpSmashTarget(target);
			break;
		case 2:
			JumpSmashInPlace();
			break;
		default:
			break;
		}
	}
}

BossStates ABossCharacter::GetCurrentState()
{
	return this->currentState;
}

FVector ABossCharacter::GetAttackDestination()
{
	return this->attackDestination;
}

AActor* ABossCharacter::GetTargetActor()
{
	return this->player;
}

void ABossCharacter::ReturnToIdle()
{
	this->currentState = BossStates::Idle;
	this->currentReloadTime = 0;
	this->isImmuneToKnockback = false;
}

void ABossCharacter::SetJumping(bool jumping)
{
	this->isJumping = jumping;
}

bool ABossCharacter::GetJumping()
{
	return this->isJumping;
}

bool ABossCharacter::GetWindingUp()
{
	return this->isWindingUp;
}

void ABossCharacter::ChargeTarget(AActor* target)
{
	this->attackDestination = target->GetActorLocation();
	this->player = target;
	this->currentState = BossStates::Charge;
	this->isWindingUp = true;
}

void ABossCharacter::JumpSmashTarget(AActor* target)
{
	this->attackDestination = target->GetActorLocation();
	this->player = target;
	this->isJumping = true;
	this->currentState = BossStates::JumpAttack;
	this->isWindingUp = true;
	//GetWorld()->GetTimerManager().SetTimer(WindupTimer, this, &ABossCharacter::OnFinishWindup, 2.0f, false);
}

void ABossCharacter::JumpSmashInPlace()
{
	this->attackDestination = this->GetActorLocation();
	this->isJumping = true;
	this->currentState = BossStates::GroundSlam;
	this->isWindingUp = true;
	//GetWorld()->GetTimerManager().SetTimer(WindupTimer, this, &ABossCharacter::OnFinishWindup, 5.0f, false);
}

void ABossCharacter::OnFinishWindup()
{
	this->isWindingUp = false;
}
