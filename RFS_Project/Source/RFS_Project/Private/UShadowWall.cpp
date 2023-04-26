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
	bAlive = false;
}

void AUShadowWall::OnDamage(float Damage, AActor* ActorDamagedBy)
{
	//Return if not alive and active
	if (!bAlive)
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
	BPI_SparksDamage();
	if (HitPoints < 0)
	{
		OnDeath();
		//If this is not the 'CurrentWall', flash the player
		if (!bISPlayerInside)
		{
			BPI_FlashActor(ActorDamagedBy);
		}
	}
}

void AUShadowWall::OnHeal(float heal)
{
	//Don't heal if we're not alive and active
	if (bAlive)
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

void AUShadowWall::OnDeath()
{
	bAlive = false;
	OwningPlayer = nullptr;
	BPI_OnDeath();
}


// Called every frame
void AUShadowWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AUShadowWall::StartWall(int i, bool Player, AActor* NewOwner)
{
	ChangeVisibility(true);
	HitPoints = MaxHitPoints;
	OwningPlayer = NewOwner;
	bAlive = true;

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
