// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:
	UBehaviorTreeComponent* BehaviorTreeComp;
	UBlackboardComponent* BlackboardComp;
	
protected:
    virtual void OnPossess(APawn *InPawn) override;

public:
	AEnemyController();

	UPROPERTY(EditAnywhere, Category = "AI")
		UAIPerceptionComponent* AIPerceptionComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BlackboardTarget = "EnemyActor";
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BlackboardSeesTarget = "HasLineOfSight";

	UFUNCTION() void UpdateSeenTarget(AActor* InActor, FAIStimulus Stimulus);

	void OnTargetSightLost();

private:
	FTimerHandle StartEnemyTimer;
	float LineOfSightTimer = 4.0f;

	UFUNCTION() void OnLostTarget();
};
