// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayableCharacter.h"
#include "AGun.h"
#include "../Combat.h"
#include "AEnemyCharacter.generated.h"

UCLASS()
/*A base class for the enemy combat AI functionanlity*/
class RFS_PROJECT_API AAEnemyCharacter : public APlayableCharacter
{
	GENERATED_BODY()

public:
	/*
	* Called every game tick
	* @param DeltaTime - Time between ticks
	*/
	virtual void Tick(float DeltaTime) override;
	//TODO investigate don't think this is needed
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/* Default constructor*/
	AAEnemyCharacter();
	/*
	* Updates character walk speed
	* @param Speed - New walk speed
	*/
	void UpdateWalkSpeed(float Speed);
	/*
	* Blueprint-callable function for having enemy shoot their gun
	* @param StartHitScanLoc - Start of line trace for the shot
	*/
	UFUNCTION(BlueprintCallable)
		void ShootGun(FVector StartHitScanLoc);
public:
	/* Delegate called upon enemy respawn */
	DECLARE_DYNAMIC_DELEGATE(FRespawned);
	FRespawned OnRespawn;
	/* Health for the enemy*/
	UPROPERTY(EditAnywhere)
		float CharacterHealth;
	/* Gun equipped to the enemy*/
	UPROPERTY(EditAnywhere)
		AAGun* EquippedGun;
	
protected:
	/*Called when the game starts or actor is spawned*/
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
	/* For defining what happens when player is killed*/
	void OnKill() override {};
protected:
	/* Point for respawn of enemy*/
	FVector RespawnPoint;
	/* Last actor that damaged the enemy*/
	AActor* SavedActorDamageBy;
};
