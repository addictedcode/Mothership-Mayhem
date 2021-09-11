// Fill out your copyright notice in the Description page of Project Settings.


#include "MothershipMayhem/Public/Character/MMCharacterBase.h"
#include "Gun/MMGunLoadout.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMMCharacterBase::AMMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	#pragma region Player Mesh
	// Create a gun mesh component
	tempMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tempMesh"));
	tempMesh->bCastDynamicShadow = false;
	tempMesh->CastShadow = false;
	tempMesh->SetupAttachment(RootComponent);
	#pragma endregion 

	#pragma region Camera Component
	// Create a CameraComponent	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("firstPersonCamera"));
	cameraComponent->SetupAttachment(GetCapsuleComponent());
	cameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	cameraComponent->bUsePawnControlRotation = true;
	#pragma endregion

	#pragma region Gun Loadout Component
	//Create Gun Loadout Component
	gunLoadoutComponent = CreateDefaultSubobject<UMMGunLoadout>(TEXT("PlayerGunLoadout"));
	gunLoadoutComponent->bulletPool = &this->bulletPool;
	#pragma endregion 
}

// Called when the game starts or when spawned
void AMMCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> children;
	this->GetComponents(children, true);
	for (int i = 0; i < children.Num(); i++)
	{
		UActorComponent* child = children[i];
		FString name = child->GetName();
		if (child->GetName() == "VacuumHitbox")
		{
			gunLoadoutComponent->setVacuumHitbox(Cast<UBoxComponent>(child));
		}
	}

	if (tempMesh->DoesSocketExist("GripPoint")) {
		const FRotator gunRotation = tempMesh->GetSocketRotation("GripPoint");
		const FVector gunLocation = tempMesh->GetSocketLocation("GripPoint");

		gunLoadoutComponent->SetWorldLocationAndRotation(gunLocation, gunRotation);
		gunLoadoutComponent->AttachToComponent(cameraComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
	
}

// Called to bind functionality to input
void AMMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Character Movement
	/*PlayerInputComponent->BindAxis("MoveX", this, &AMMCharacterBase::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &AMMCharacterBase::MoveY);*/

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMMCharacterBase::StartJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMMCharacterBase::EndJump);
	
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMMCharacterBase::StartCrouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMMCharacterBase::EndCrouch);
	
	//Mouse Movement
	/*PlayerInputComponent->BindAxis("MouseX", this, &AMMCharacterBase::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &AMMCharacterBase::MouseY);*/

	//Gun Controls
	/*PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &AMMCharacterBase::OnPrimaryShootPressed);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &AMMCharacterBase::OnPrimaryShootReleased);
	PlayerInputComponent->BindAxis("SwapGunWheel", this, &AMMCharacterBase::OnSwapWheel);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMMCharacterBase::OnReload);*/

}

#pragma region Character Movement

void AMMCharacterBase::MoveX(float value)
{
	if (uint8(m_State & MMCharacterState::Grappling)) 
		return;
	
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
	if (uint8(m_State & MMCharacterState::Grappling))
		return;
	
	if ((Controller) && (value != 0.0f))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

void AMMCharacterBase::StartJump()
{
	Jump();
	m_State |= MMCharacterState::Jumping;
}

void AMMCharacterBase::EndJump()
{
	StopJumping();
	m_State &= ~MMCharacterState::Jumping;
}


void AMMCharacterBase::StartCrouch()
{
	Crouch(true);
	m_State |= MMCharacterState::Crouching;
}

void AMMCharacterBase::EndCrouch()
{
	UnCrouch(true);
	m_State &= ~MMCharacterState::Crouching;
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

#pragma region Gun

void AMMCharacterBase::OnPrimaryShootPressed()
{
	if (gunLoadoutComponent != NULL) {
		gunLoadoutComponent->OnPrimaryShootPressed();
	}
}

void AMMCharacterBase::OnPrimaryShootReleased()
{
	if (gunLoadoutComponent != NULL) {
		gunLoadoutComponent->OnPrimaryShootReleased();
	}
}

void AMMCharacterBase::OnSwapWheel(float value)
{
	if (value != 0)
	{
		if (gunLoadoutComponent != NULL) {
			gunLoadoutComponent->OnSwapWheel(value);
		}
	}
}

void AMMCharacterBase::OnReload()
{
	if (gunLoadoutComponent != NULL) {
		gunLoadoutComponent->OnReload();
	}
}

#pragma endregion 