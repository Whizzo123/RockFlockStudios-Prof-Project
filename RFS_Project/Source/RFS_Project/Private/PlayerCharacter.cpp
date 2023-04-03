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
	MaxHitPoints = HitPoints = CharacterHealth;
	RespawnPoint = GetActorLocation();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentMovementState == EPlayerMovementState::Walking)
	{
		if (GetCharacterMovement()->IsWalking() == false)
		{
			CurrentMovementState = EPlayerMovementState::StandingStill;
			// Need access to equipped gun -> then sort other transition states pls :)
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::OnHeal(float Health)
{
	HitPoints += Health;
	if (HitPoints > MaxHitPoints)
		HitPoints = MaxHitPoints;
}

void APlayerCharacter::OnDamage(float Damage, AActor* ActorDamagedBy)
{
	BPI_TakeDamage();
	HitPoints -= Damage;
	if (HitPoints <= 0)
		OnDeath();
}

void APlayerCharacter::OnDeath()
{
	SetActorLocation(RespawnPoint);
	HitPoints = MaxHitPoints;
}

void APlayerCharacter::CreateHint()
{
	OnAIHint.Broadcast(this, 10.0f);
}

void APlayerCharacter::SetToSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = CharacterSprintSpeed;
}

void APlayerCharacter::SetToWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = CharacterWalkSpeed;
}

void APlayerCharacter::SetToCrouch()
{
	GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterCrouchSpeed;
}
