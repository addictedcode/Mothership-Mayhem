// Fill out your copyright notice in the Description page of Project Settings.


#include "MothershipMayhem/Public/Gun/MMGunBase.h"
#include "Projectiles/MMProjectileBase.h"

// Sets default values
AMMGunBase::AMMGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	#pragma region Gun Mesh
	// Create a gun mesh component
	gunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("gunMesh"));
	gunMesh->bCastDynamicShadow = false;
	gunMesh->CastShadow = false;
	gunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	gunMesh->SetupAttachment(RootComponent);
	#pragma endregion 
}

// Called when the game starts or when spawned
void AMMGunBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMMGunBase::SetMesh(UStaticMesh* newStaticMesh)
{
	if (gunMesh != NULL)
	{
		gunMesh->SetStaticMesh(newStaticMesh);
	}
}

void AMMGunBase::SetProjectile(TSubclassOf<AMMProjectileBase> newProjectileClass)
{
	projectileClass = newProjectileClass;
}

bool AMMGunBase::OnShoot()
{
	if (projectileClass == NULL)
	{
		return false;
	}
	
	UWorld* const world = this->GetWorld();

	if (world == NULL) 
	{
		return false;
	}

	if (!gunMesh->DoesSocketExist("MuzzlePoint"))
	{
		return false;
	}

	UE_LOG(LogTemp, Display, TEXT("%f"), gunStats.currentAmmo);
	
	const FRotator SpawnRotation = gunMesh->GetSocketRotation("MuzzlePoint");
	const FVector SpawnLocation = gunMesh->GetSocketLocation("MuzzlePoint");

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// spawn the projectile at the muzzle
	world->SpawnActor<AMMProjectileBase>(projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	return true;
}


