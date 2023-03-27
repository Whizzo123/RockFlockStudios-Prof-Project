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
class RFS_PROJECT_API AAEnemyCharacter : public APlayableCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAEnemyCharacter();
	//Delegate called upon AI respawn
	DECLARE_DYNAMIC_DELEGATE(FRespawned);
	FRespawned OnRespawn;
	//UPROPERTIES
	UPROPERTY(EditAnywhere)
		float CharacterHealth;
	UPROPERTY(EditAnywhere)
		AAGun* EquippedGun;
	//UFUNCTIONS
	UFUNCTION(BlueprintCallable)
		void ShootGun(FVector StartHitScanLoc);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnHeal(float Health) override;
	void OnDamage(float Damage, AActor* ActorDamagedBy) override;
	void OnDeath() override;
	void OnKill() override {};

	FVector RespawnPoint;
	AActor* SavedActorDamageBy;


	UFUNCTION(BlueprintNativeEvent)
	void BPI_OnDeath();

	void BPI_OnDeath_Implementation() {};
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateWalkSpeed(float Speed);
};
