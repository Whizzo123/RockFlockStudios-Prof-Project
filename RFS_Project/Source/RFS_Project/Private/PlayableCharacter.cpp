// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitPoints = 5;
	MaxHitPoints = 5;

}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	MaxHitPoints = HitPoints;
	RespawnPoint = GetActorLocation();
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayableCharacter::OnHeal_Implementation(float Health)
{
	HitPoints += Health;
	if (HitPoints > MaxHitPoints)
	{
		HitPoints = MaxHitPoints;
	}
}

void APlayableCharacter::OnDamage_Implementation(float Damage, AActor* ActorDamagedBy)
{
	SavedActorDamageBy = ActorDamagedBy;
	HitPoints -= Damage;
	if (HitPoints <= 0)
	{
		IHealth::Execute_OnDeath(this);
	}
	IHealth::Execute_BPI_OnDamage(this, 1.0f, ActorDamagedBy);
}

void APlayableCharacter::OnKill_Implementation()
{
	IHealth::Execute_BPI_OnKill(this);
}

void APlayableCharacter::OnDeath_Implementation()
{
	bool bImplementsHealth = UKismetSystemLibrary::DoesImplementInterface(SavedActorDamageBy, UHealth::StaticClass());
	
	if (bImplementsHealth)
	{
		IHealth::Execute_OnKill(SavedActorDamageBy);
	}
	IHealth::Execute_BPI_OnDeath(this);
	SetActorLocation(RespawnPoint);
	HitPoints = MaxHitPoints;
}

void APlayableCharacter::PlayReloadAnimation()
{
	GetMesh()->PlayAnimation(ReloadAnim, false);
}

