// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "IShadowPawn.h"
#include "../Combat.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	UFUNCTION(BlueprintCallable)
		void SetToSprint();
	UFUNCTION(BlueprintCallable)
		void SetToWalk();
	UFUNCTION(BlueprintCallable)
		void SetToCrouch();
public:
	/* Delegate for when sending hint to AI */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIHint, AActor*, Player, float, hintTime);
	FAIHint OnAIHint;
	/* Health for the player character */
	UPROPERTY(EditAnywhere)
		float CharacterHealth;
	UPROPERTY(EditAnywhere)
		float CharacterSprintSpeed;
	UPROPERTY(EditAnywhere)
		float CharacterWalkSpeed;
	UPROPERTY(EditAnywhere)
		float CharacterCrouchSpeed;
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
	/* Blueprint-implementable event for defining what happens when player is killed*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnKill() override;
	/* Blueprint-implementable event for defining what happens when player takes damage*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BPI_TakeDamage();
protected:
	/* Respawn Point for player*/
	FVector RespawnPoint;
};
