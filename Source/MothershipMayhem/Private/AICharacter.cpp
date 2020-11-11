// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::UpdateWalkSpeed(float newWalkSpeed)
{
	UCharacterMovementComponent* CharaMovement = GetCharacterMovement();
	if (CharaMovement)
	{
		CharaMovement->MaxWalkSpeed = newWalkSpeed;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO character movement component"));
	}
}

