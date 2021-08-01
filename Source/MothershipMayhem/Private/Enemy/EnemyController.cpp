// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy/AICharacter.h"
#include "Perception/AISense_Sight.h"
#include "Enemy/EnemyFactory.h"
#include "Character/MMCharacterBase.h"

void AEnemyController::OnPossess(APawn *InPawn) {
	Super::OnPossess(InPawn);

	AAICharacter* AICharacter = Cast<AAICharacter>(InPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
			BehaviorTreeComp->StartTree(*AICharacter->BehaviorTree);

			BlackboardComp->SetValueAsFloat(BlackboardWalkSpeed, 125.0f);
			BlackboardComp->SetValueAsFloat(BlackboardRunSpeed, 500.0f);
			BlackboardComp->SetValueAsFloat(BlackboardAttackRange, 800.0f);

			EnemyFactory::InitializeEnemy("baseEnemy", AICharacter, this);

			AMMCharacterBase* player = Cast<AMMCharacterBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
			if (player != nullptr)
			{
				BlackboardComp->SetValueAsObject(BlackboardTarget, player);
				BlackboardComp->SetValueAsBool(BlackboardChasingTarget, true);
				BlackboardComp->SetValueAsBool(BlackboardSeesTarget, false);
			}
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
			if (InActor == BlackboardComp->GetValueAsObject(BlackboardTarget)) {
				if (Stimulus.WasSuccessfullySensed()) {
					//GetWorld()->GetTimerManager().ClearTimer(StartEnemyTimer);
					//BlackboardComp->SetValueAsObject(BlackboardTarget, InActor);
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

void AEnemyController::SetNewTarget(AActor* newTarget)
{
	if (BlackboardComp)
	{
		if (newTarget)
		{
			if (newTarget->ActorHasTag("Player")) {
				BlackboardComp->SetValueAsObject(BlackboardTarget, newTarget);
				BlackboardComp->SetValueAsBool(BlackboardChasingTarget, true);
				BlackboardComp->SetValueAsBool(BlackboardSeesTarget, false);
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
		//GetWorld()->GetTimerManager().SetTimer(StartEnemyTimer, this, &AEnemyController::OnLostTarget, LineOfSightTimer, false);
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
		UpdateWalkSpeed(BlackboardComp->GetValueAsFloat(BlackboardWalkSpeed) * 3);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blackboard assigned"));
	}
}

void AEnemyController::UpdateAttackRange(float newRange)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(BlackboardAttackRange, newRange);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blackboard assigned"));
	}
}

void AEnemyController::UpdateRunSpeed(float newSpeed)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(BlackboardRunSpeed, newSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO Blackboard assigned"));
	}
}

void AEnemyController::UpdateWalkSpeed(float newSpeed)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(BlackboardWalkSpeed, newSpeed);
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
	UpdateWalkSpeed(BlackboardComp->GetValueAsFloat(BlackboardWalkSpeed) / 3);
}
