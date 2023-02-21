// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MaxHitPoints = HitPoints = characterHealth;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::OnHeal(float health)
{
	HitPoints += health;
	if (HitPoints > MaxHitPoints)
		HitPoints = MaxHitPoints;
}

void APlayerCharacter::OnDamage(float damage)
{
	HitPoints -= damage;
	if (HitPoints <= 0)
		OnDeath();
}

void APlayerCharacter::OnDeath()
{
	Destroy();
}

void APlayerCharacter::OnHitByBullet(float bulletDamage)
{
	OnDamage(bulletDamage);
}

void APlayerCharacter::CreateHint()
{
	OnAIHint.Broadcast(this, 10.0f);
}
