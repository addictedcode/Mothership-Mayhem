// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MMCharacterController.h"

void AMMCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void AMMCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UInputComponent* PlayerInputComponent = this->FindComponentByClass<UInputComponent>();
	if (PlayerInputComponent != NULL) {
		//Character Movement
		PlayerInputComponent->BindAxis("MoveX", this, &AMMCharacterController::MoveX);
		PlayerInputComponent->BindAxis("MoveY", this, &AMMCharacterController::MoveY);

		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMMCharacterController::StartJump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMMCharacterController::EndJump);

		PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMMCharacterController::StartCrouch);
		PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMMCharacterController::EndCrouch);

		//Mouse Movement
		PlayerInputComponent->BindAxis("MouseX", this, &AMMCharacterController::MouseX);
		PlayerInputComponent->BindAxis("MouseY", this, &AMMCharacterController::MouseY);

		//Gun Controls
		PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &AMMCharacterController::OnPrimaryShootPressed);
		PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &AMMCharacterController::OnPrimaryShootReleased);
		PlayerInputComponent->BindAxis("SwapGunWheel", this, &AMMCharacterController::OnSwapWheel);
		PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMMCharacterController::OnReload);
	}
	

}

#pragma region Character Movement

void AMMCharacterController::MoveX(float value)
{
	//this->characterCopy->MoveX(value);
	this->GetPawn<AMMCharacterBase>()->MoveX(value);
}

void AMMCharacterController::MoveY(float value)
{
	//this->characterCopy->MoveY(value);
	this->GetPawn<AMMCharacterBase>()->MoveY(value);
}

void AMMCharacterController::StartJump()
{
	this->GetPawn<AMMCharacterBase>()->StartJump();
}

void AMMCharacterController::EndJump()
{
	this->GetPawn<AMMCharacterBase>()->EndJump();
}

void AMMCharacterController::StartCrouch()
{
	this->GetPawn<AMMCharacterBase>()->StartCrouch();
}

void AMMCharacterController::EndCrouch()
{
	this->GetPawn<AMMCharacterBase>()->EndCrouch();
}


#pragma endregion

#pragma region Mouse Movement

void AMMCharacterController::MouseX(float value)
{
	this->GetPawn<AMMCharacterBase>()->MouseX(value);
}

void AMMCharacterController::MouseY(float value)
{
	this->GetPawn<AMMCharacterBase>()->MouseY(value);
}

#pragma endregion

#pragma region Gun

void AMMCharacterController::OnPrimaryShootPressed()
{
	this->GetPawn<AMMCharacterBase>()->OnPrimaryShootPressed();
}

void AMMCharacterController::OnPrimaryShootReleased()
{
	this->GetPawn<AMMCharacterBase>()->OnPrimaryShootReleased();
}

void AMMCharacterController::OnSwapWheel(float value)
{
	this->GetPawn<AMMCharacterBase>()->OnSwapWheel(value);
}

void AMMCharacterController::OnReload()
{
	this->GetPawn<AMMCharacterBase>()->OnReload();
}