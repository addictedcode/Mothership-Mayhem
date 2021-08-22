// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AICharacter.h"
#include "BossCharacter.generated.h"

UENUM(BlueprintType)
enum class BossStates : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Charge UMETA(DisplayName = "Charge"),
	JumpAttack UMETA(DisplayName = "JumpAttack"),
	GroundSlam UMETA(DisplayName = "GroundSlam")
};
/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API ABossCharacter : public AAICharacter
{
	GENERATED_BODY()
	
public:
	ABossCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	/*Chooses which of the boss action functions to use*/
	UFUNCTION(BlueprintCallable)
		virtual void SelectMoveIndex(int index, AActor* target);

	//blueprint called functions to damage the player due to its stat component being blueprint only
	UFUNCTION(BlueprintCallable)
		BossStates GetCurrentState();
	
	UFUNCTION(BlueprintCallable)
		FVector GetAttackDestination();
	
	UFUNCTION(BlueprintCallable)
		AActor* GetTargetActor();
	
	UFUNCTION(BlueprintCallable)
		void ReturnToIdle();
	
	UFUNCTION(BlueprintCallable)
		void SetJumping(bool jumping);
	
	UFUNCTION(BlueprintCallable)
		bool GetJumping();
	
	UFUNCTION(BlueprintCallable)
		bool GetWindingUp();
	UFUNCTION(BlueprintCallable)
		void OnFinishWindup();

private:
	void ChargeTarget(AActor* target);

	void JumpSmashTarget(AActor* target);

	void JumpSmashInPlace();

	FVector attackDestination;
	UPROPERTY(EditAnywhere, Category = "AI")
		BossStates currentState = BossStates::Idle;

	bool isJumping = false;

	FTimerHandle WindupTimer;
	bool isWindingUp = false;
};
