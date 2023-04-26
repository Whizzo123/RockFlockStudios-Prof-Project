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

void APlayableCharacter::OnDamage(float Damage, AActor* ActorDamagedBy)
{
	SavedActorDamageBy = ActorDamagedBy;
	HitPoints -= Damage;
	if (HitPoints <= 0)
	{
		OnDeath();
	}
	CharacterDamagedEvent(ActorDamagedBy);
}

void APlayableCharacter::OnDeath()
{
	if (SavedActorDamageBy)
	{
		IHealth* HealthComponent = Cast<IHealth>(SavedActorDamageBy);
		if (HealthComponent)
		{
			HealthComponent->OnKill();
		}
	}
	BPI_OnDeath();
	SetActorLocation(RespawnPoint);
	HitPoints = MaxHitPoints;
}

void APlayableCharacter::PlayReloadAnimation()
{
	GetMesh()->PlayAnimation(ReloadAnim, false);
}

