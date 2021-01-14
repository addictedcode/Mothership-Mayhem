// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy/AICharacter.h"
#include "Perception/AISense_Sight.h"

void AEnemyController::OnPossess(APawn *InPawn) {
	Super::OnPossess(InPawn);

	AAICharacter* AICharacter = Cast<AAICharacter>(InPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
			BehaviorTreeComp->StartTree(*AICharacter->BehaviorTree);
		}

		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::UpdateSeenTarget);
	}
}

AEnemyController::AEnemyController()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	/*FAISenseID SenseID = UAISense::GetSenseID<UAISense_Sight>();
	UAISenseConfig* SenseConfig = Cast<UAISenseConfig>(AIPerceptionComp->GetSenseConfig(SenseID));
	if (SenseConfig)
	{
		AIPerceptionComp->ConfigureSense(*SenseConfig);
	}*/
	
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AEnemyController::UpdateSeenTarget(AActor* InActor, FAIStimulus Stimulus)
{
	if (BlackboardComp)
	{
		if (InActor)
		{
			if (InActor->ActorHasTag("Player")) {
				if (Stimulus.WasSuccessfullySensed()) {
					GetWorld()->GetTimerManager().ClearTimer(StartEnemyTimer);
					BlackboardComp->SetValueAsObject(BlackboardTarget, InActor);
					BlackboardComp->SetValueAsBool(BlackboardChasingTarget, true);
					BlackboardComp->SetValueAsBool(BlackboardSeesTarget, true);
				}
				else
				{
					OnTargetSightLost();
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blackboard assigned"));
	}
}

void AEnemyController::OnTargetSightLost()
{
	if (BlackboardComp)
	{
		GetWorld()->GetTimerManager().SetTimer(StartEnemyTimer, this, &AEnemyController::OnLostTarget, LineOfSightTimer, false);
		BlackboardComp->SetValueAsBool(BlackboardSeesTarget, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blackboard assigned"));
	}
}

void AEnemyController::OnCharacterDisoriented(float duration)
{
	if (BlackboardComp)
	{
		GetWorld()->GetTimerManager().SetTimer(disorientationTimer, this, &AEnemyController::ClearDisorientation, duration, false);
		BlackboardComp->SetValueAsBool(BlackboardIsDisoriented, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blackboard assigned"));
	}
}

void AEnemyController::OnLostTarget()
{
	BlackboardComp->SetValueAsObject(BlackboardTarget, nullptr);
	BlackboardComp->SetValueAsBool(BlackboardChasingTarget, false);
}

void AEnemyController::ClearDisorientation()
{
	BlackboardComp->SetValueAsBool(BlackboardIsDisoriented, false);
}
