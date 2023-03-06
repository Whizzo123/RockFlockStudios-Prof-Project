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
	//UPROPERTIES
	UPROPERTY(EditAnywhere)
		float characterHealth;
	UPROPERTY(EditAnywhere)
		AAGun* equippedGun;
	//UFUNCTIONS
	UFUNCTION(BlueprintCallable)
		void OnHitByBullet(float bulletDamage);
	UFUNCTION(BlueprintCallable)
		void ShootGun();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnHeal(float health) override;
	void OnDamage(float damage) override;
	void OnDeath() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateWalkSpeed(float speed);
};
