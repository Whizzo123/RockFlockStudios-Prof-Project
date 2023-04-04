// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "IShadowPawn.h"
#include "../Combat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AGun.h"
#include "PlayerCharacter.generated.h"

UCLASS()
/*A class for the base functionality of the player in the game*/
class RFS_PROJECT_API APlayerCharacter : public APlayableCharacter, public IShadowPawn
{
	GENERATED_BODY()
public:
	/*
	* Called every game tick
	* @param DeltaTime - Time between ticks
	*/
	virtual void Tick(float DeltaTime) override;
	/*
	*  Called to bind functionality to input
	*  @param PlayerInputComponent - Input component for the player
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/* Sets default values for this character's properties */
	APlayerCharacter();
	/* Blueprint-callable function that creates a hint for the AI of the player location */
	UFUNCTION(BlueprintCallable)
		void CreateHint();
	/*
	* Blueprint-callable function that sets the player to sprint
	* @param ToOverride - Whether this will switch the state regardless of the current state
	*/
	UFUNCTION(BlueprintCallable)
		void SetToSprint(bool ToOverride = false);
	/* 
	* Blueprint-callable function that sets the player to walk
	* @param ToOverride - Whether this will switch the state regardless of the current state
	*/
	UFUNCTION(BlueprintCallable)
		void SetToWalk(bool ToOverride = false);
	/* Blueprint-callable function that sets the player to crouch*/
	UFUNCTION(BlueprintCallable)
		void SetToCrouch();
	/* Blueprint-callable function that sets the player to jump*/
	UFUNCTION(BlueprintCallable)
		void SetToJump();
public:
	/* Delegate for when sending hint to AI */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIHint, AActor*, Player, float, hintTime);
	FAIHint OnAIHint;
	/* Health for the player character */
	UPROPERTY(EditAnywhere)
		float CharacterHealth;
	/* Speed for sprinting*/
	UPROPERTY(EditAnywhere)
		float CharacterSprintSpeed;
	/* Speed for walking*/
	UPROPERTY(EditAnywhere)
		float CharacterWalkSpeed;
	/* Speed for crouching*/
	UPROPERTY(EditAnywhere)
		float CharacterCrouchSpeed;
	/* Accuracy debuff for sprinting*/
	UPROPERTY(EditAnywhere)
		float SprintingAccuracyDebuffPercentage;
	/* Accuracy debuff for walking*/
	UPROPERTY(EditAnywhere)
		float WalkingAccuracyDebuffPercentage;
	/* Accuracy debuff for jumping*/
	UPROPERTY(EditAnywhere)
		float JumpingAccuracyDebuffPercentage;
	/* Accuracy buff for crouching*/
	UPROPERTY(EditAnywhere)
		float CrouchingAccuracyBuffPercentage;
	/* Reference to the equipped gun on the player*/
	UPROPERTY(BlueprintReadWrite)
		AAGun* EquippedGun;
protected:
	/* Called when the game starts or this actor is spawned*/
	virtual void BeginPlay() override;
	/*
	* Called to heal the player
	* @param Health - Amount to heal player by
	*/
	void OnHeal(float Health) override;
	/*
	* Called to damage the player
	* @param Damage - Amount to damage player by
	* @param ActorDamagedBy - Actor that caused the damage
	*/
	void OnDamage(float Damage, AActor* ActorDamagedBy) override;
	/* Called when player is killed */
	void OnDeath() override;
	/* Function for updating player movement state*/
	void UpdatePlayerMovementState();
	/* Function for switching player movement states*/
	void SwitchMovementState(EPlayerMovementState NewState);
	/* Blueprint-implementable event for defining what happens when player is killed*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnKill() override;
	/* Blueprint-implementable event for defining what happens when player takes damage*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BPI_TakeDamage();
protected:
	/* Respawn Point for player*/
	FVector RespawnPoint;
	/* Current player movement state*/
	EPlayerMovementState CurrentMovementState;
	/* Last player movement state*/
	EPlayerMovementState LastMovementState;
};

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	StandingStill UMETA(DisplayName = "Standing Still"),
	Crouching UMETA(DisplayName = "Crouching"),
	Walking UMETA(DisplayName = "Walking"),
	Sprinting UMETA(DisplayName = "Sprinting"),
	Jumping UMETA(DisplayName = "Jumping")
};