// Fill out your copyright notice in the Description page of Project Settings.


#include "UShadowWall.h"

// Sets default values
AUShadowWall::AUShadowWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Scene Root Component");
	WallPlane = CreateDefaultSubobject<UStaticMeshComponent>("Wall Plane");

	SetRootComponent(SceneRootComponent);
	WallPlane->SetupAttachment(RootComponent);
	
}
// Called when the game starts or when spawned
void AUShadowWall::BeginPlay()
{
	Super::BeginPlay();
	ChangeVisibility(false);
	HitPoints = MaxHitPoints;
	bInUse = false;
}

void AUShadowWall::OnDamage_Implementation(float Damage, AActor* ActorDamagedBy)
{
	//Return if its not in use or if HitPoints is already below 0
	if (!bInUse || HitPoints < 0)
	{
		return;
	}
	//Take no damage if owned
	if (ActorDamagedBy == OwningPlayer)
	{
		return;
	}

	//Take Damage and check for Death
	HitPoints -= Damage;
	IHealth::Execute_BPI_OnDamage(this, 1.0f, ActorDamagedBy);
	if (HitPoints < 0)
	{
		IHealth::Execute_OnDeath(this);
		//If this is not the 'CurrentWall', flash the player
		if (!bISPlayerInside)
		{
			BPI_FlashActor(ActorDamagedBy);
		}
	}
}

void AUShadowWall::OnHeal_Implementation(float heal)
{
	//Don't heal if we're not alive and active
	if (bInUse)
	{
		return;
	}
	//Heal up to max hit points
	HitPoints += heal;
	if (HitPoints > MaxHitPoints)
	{
		HitPoints = MaxHitPoints;
	}

}

void AUShadowWall::OnDeath_Implementation()
{
	HitPoints = -1;
	OwningPlayer = nullptr;
	IHealth::Execute_BPI_OnDeath(this);
}

void AUShadowWall::OnKill_Implementation()
{
}


// Called every frame
void AUShadowWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AUShadowWall::EndWall()
{
	HitPoints = -1;
	OwningPlayer = nullptr;
	IHealth::Execute_BPI_OnDeath(this);
}

void AUShadowWall::StartWall(int i, bool Player, AActor* NewOwner)
{
	ChangeVisibility(true);
	HitPoints = MaxHitPoints;
	OwningPlayer = NewOwner;
	bInUse = true;

	ChangeWallTextures(i, Player);
}

void AUShadowWall::ChangeVisibility(bool Visible)
{
	if (!WallPlane)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No Plane Found"));
		return;
	}
	WallPlane->SetVisibility(Visible);
}
