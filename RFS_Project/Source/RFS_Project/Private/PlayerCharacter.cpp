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
	if (EquippedGun)
	{
		UpdatePlayerMovementState();
	}
}

void APlayerCharacter::UpdatePlayerMovementState()
{
	UCharacterMovementComponent* component = GetCharacterMovement();
	switch (CurrentMovementState)
	{
		case EPlayerMovementState::StandingStill:
		{
			// Are we moving?
			if (component->Velocity.Length() > 0)
			{
				SetToWalk();
			}
			break;
		}
		case EPlayerMovementState::Jumping:
		{
			// We are not jumping anymore
			if (component->IsWalking() == true)
			{
				// Are we moving?
				if (component->Velocity.Length() > 0)
				{
					if (LastMovementState == EPlayerMovementState::Walking)
					{
						SetToWalk(true);
					}
					else if (LastMovementState == EPlayerMovementState::Sprinting)
					{
						SetToSprint(true);
					}
				}
				else
				{
					SwitchMovementState(EPlayerMovementState::StandingStill);
					GunAccuracy(0);
				}
			}
			break;
		}
		case EPlayerMovementState::Walking:
		{
			if (component->Velocity.Length() == 0)
			{
				SwitchMovementState(EPlayerMovementState::StandingStill);
				GunAccuracy(0);
			}
			break;
		}
	}
}

void APlayerCharacter::SwitchMovementState(EPlayerMovementState NewState)
{
	LastMovementState = CurrentMovementState;
	CurrentMovementState = NewState;
}

void APlayerCharacter::GunAccuracy(float Modifier)
{
	if (EquippedGun)
	{
		EquippedGun->ResetGunAccuracyModifier();
		EquippedGun->AlterGunAccuracyModifier(Modifier);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::CreateHint(AActor* Actor, float HintTime)
{
	OnAIHint.Broadcast(Actor, HintTime);
}

void APlayerCharacter::SetToSprint(bool ToOverride)
{
	GetCharacterMovement()->MaxWalkSpeed = CharacterSprintSpeed;
	if (CurrentMovementState == EPlayerMovementState::Jumping && ToOverride == false)
	{
		LastMovementState = EPlayerMovementState::Sprinting;
	}
	else
	{
		SwitchMovementState(EPlayerMovementState::Sprinting);
		GunAccuracy(SprintingAccuracyDebuffPercentage);

	}
}

void APlayerCharacter::SetToWalk(bool ToOverride)
{
	GetCharacterMovement()->MaxWalkSpeed = CharacterWalkSpeed;
	if (CurrentMovementState == EPlayerMovementState::Jumping && ToOverride == false)
	{
		LastMovementState = EPlayerMovementState::Walking;
	}
	else
	{
		SwitchMovementState(EPlayerMovementState::Walking);
		GunAccuracy(WalkingAccuracyDebuffPercentage);

	}
}

void APlayerCharacter::SetToCrouch()
{
	GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterCrouchSpeed;
	SwitchMovementState(EPlayerMovementState::Crouching);
	GunAccuracy(CrouchingAccuracyBuffPercentage);

}

void APlayerCharacter::SetToJump()
{
	SwitchMovementState(EPlayerMovementState::Jumping);
	GunAccuracy(JumpingAccuracyDebuffPercentage);

}
