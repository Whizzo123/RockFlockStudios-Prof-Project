// Fill out your copyright notice in the Description page of Project Settings.


#include "AEnemyCharacter.h"

// Sets default values
AAEnemyCharacter::AAEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	MaxHitPoints = HitPoints = CharacterHealth;
	RespawnPoint = GetActorLocation();
	TArray<AActor*> ActorChildren;
	GetAllChildActors(ActorChildren);
	for(int i = 0; i < ActorChildren.Num(); i++)
	{
		if (Cast<AAGun>(ActorChildren[i]))
		{
			EquippedGun = Cast<AAGun>(ActorChildren[i]);
		}
	}
	if (EquippedGun)
	{
		EquippedGun->PawnEquippedTo = this;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "AAEnemyCharacter::BeginPlay() has no gun equipped");
	}
}

// Called every frame
void AAEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAEnemyCharacter::UpdateWalkSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AAEnemyCharacter::OnHeal(float Health)
{
	HitPoints += Health;
	if (HitPoints > MaxHitPoints)
	{
		HitPoints = MaxHitPoints;
	}
}

void AAEnemyCharacter::OnDamage(float Damage, AActor* ActorDamagedBy)
{
	SavedActorDamageBy = ActorDamagedBy;
	HitPoints -= Damage;
	if (HitPoints <= 0)
	{
		OnDeath();
	}
	CharacterDamagedEvent(ActorDamagedBy);
}

void AAEnemyCharacter::OnDeath()
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
	OnRespawn.Execute();
	HitPoints = MaxHitPoints;
}

void AAEnemyCharacter::ShootGun(FVector StartHitScanLoc)
{
	EquippedGun->Fire(StartHitScanLoc);
}