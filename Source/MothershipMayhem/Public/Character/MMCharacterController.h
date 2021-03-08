// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MMCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "MMCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MOTHERSHIPMAYHEM_API AMMCharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite) AMMCharacterBase* characterCopy;

private:
	// Called when the game starts or when spawned
	

	//Keyboard
	void MoveX(float value);
	void MoveY(float value);

	void StartCrouch();
	void EndCrouch();

	//Mouse
	void MouseX(float value);
	void MouseY(float value);

	//Gun
	void OnPrimaryShootPressed();
	void OnPrimaryShootReleased();
	void OnSwapWheel(float value);
	void OnReload();
};
