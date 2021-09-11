// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MMCharacterBase.generated.h"

UENUM(BlueprintType)
enum class MMCharacterState : uint8
{
	Idle =			0			UMETA(DisplayName = "Idle"),
	Crouching =		1 << 0		UMETA(DisplayName = "Crouching"),
	//Running =		1 << 1		UMETA(DisplayName = "Running"),
	Jumping =		1 << 2		UMETA(DisplayName = "Jumping"),
	//Shooting =		1 << 3		UMETA(DisplayName = "Shooting"),
	Grappling =		1 << 4		UMETA(DisplayName = "Grappling"),
};

inline MMCharacterState operator~ (MMCharacterState a) { return (MMCharacterState)~(uint8)a; }
inline MMCharacterState operator| (MMCharacterState a, MMCharacterState b) { return (MMCharacterState)((uint8)a | (uint8)b); }
inline MMCharacterState operator& (MMCharacterState a, MMCharacterState b) { return (MMCharacterState)((uint8)a & (uint8)b); }
inline MMCharacterState operator^ (MMCharacterState a, MMCharacterState b) { return (MMCharacterState)((uint8)a ^ (uint8)b); }
inline MMCharacterState& operator|= (MMCharacterState& a, MMCharacterState b) { return (MMCharacterState&)((uint8&)a |= (uint8)b); }
inline MMCharacterState& operator&= (MMCharacterState& a, MMCharacterState b) { return (MMCharacterState&)((uint8&)a &= (uint8)b); }
inline MMCharacterState& operator^= (MMCharacterState& a, MMCharacterState b) { return (MMCharacterState&)((uint8&)a ^= (uint8)b); }

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

public:

	//State
	MMCharacterState m_State;
	
	//Keyboard
	void MoveX(float value);
	void MoveY(float value);

	void StartJump();
	void EndJump();
	
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Projectile pool reference
	AActor* bulletPool = nullptr;

	// for playing gun sounds (to be called in gunbase)
	UFUNCTION(BlueprintImplementableEvent)
		void PlayShootingSound();

protected:
	/** TempMesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* tempMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* skeletalMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* cameraComponent;
	
	/**Gun Loadout */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMMGunLoadout* gunLoadoutComponent;

	
	
};
