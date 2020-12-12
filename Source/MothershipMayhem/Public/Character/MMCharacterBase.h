// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MMCharacterBase.generated.h"

UCLASS()
class MOTHERSHIPMAYHEM_API AMMCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMMCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** TempMesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* tempMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* cameraComponent;
	
	/**Gun Loadout */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMMGunLoadout* gunLoadoutComponent;
	
};
