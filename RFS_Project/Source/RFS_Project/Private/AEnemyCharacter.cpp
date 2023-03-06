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
	MaxHitPoints = HitPoints = characterHealth;
	TArray<AActor*> children;
	GetAllChildActors(children);
	for(int i = 0; i < children.Num(); i++)
	{
		if (Cast<AAGun>(children[i]))
			equippedGun = Cast<AAGun>(children[i]);
	}
	if (equippedGun)
		equippedGun->pawnEquippedTo = this;
	else
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "AAEnemyCharacter::BeginPlay() has no gun equipped");
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

void AAEnemyCharacter::UpdateWalkSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void AAEnemyCharacter::OnHeal(float health)
{
	HitPoints += health;
	if (HitPoints > MaxHitPoints)
		HitPoints = MaxHitPoints;
}

void AAEnemyCharacter::OnDamage(float damage)
{
	HitPoints -= damage;
	if (HitPoints <= 0)
		OnDeath();
}

void AAEnemyCharacter::OnDeath()
{
	Destroy();
}

void AAEnemyCharacter::OnHitByBullet(float bulletDamage)
{
	OnDamage(bulletDamage);
}

void AAEnemyCharacter::ShootGun()
{
	equippedGun->Fire();

}