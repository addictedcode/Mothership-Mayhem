// Fill out your copyright notice in the Description page of Project Settings.


#include "MothershipMayhem/Public/Character/MMCharacterBase.h"

// Sets default values
AMMCharacterBase::AMMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AMMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Character Movement
	PlayerInputComponent->BindAxis("MoveX", this, &AMMCharacterBase::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &AMMCharacterBase::MoveY);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMMCharacterBase::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMMCharacterBase::EndCrouch);
	
	//Mouse Movement
	PlayerInputComponent->BindAxis("MouseX", this, &AMMCharacterBase::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &AMMCharacterBase::MouseY);
}

#pragma region Character Movement

void AMMCharacterBase::MoveX(float value)
{
	if ((Controller) && (value != 0.0f)) 
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void AMMCharacterBase::MoveY(float value)
{
	if ((Controller) && (value != 0.0f))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

void AMMCharacterBase::StartCrouch()
{
	Crouch(true);
}

void AMMCharacterBase::EndCrouch()
{
	UnCrouch(true);
}


#pragma endregion

#pragma region Mouse Movement

void AMMCharacterBase::MouseX(float value)
{
	AddControllerYawInput(value);
}

void AMMCharacterBase::MouseY(float value)
{
	AddControllerPitchInput(value);
}

#pragma endregion 