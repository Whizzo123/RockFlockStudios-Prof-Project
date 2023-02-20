// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Combat.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RFS_PROJECT_API APlayerCharacter : public ACharacter, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	//UPROPERTIES
	UPROPERTY(EditAnywhere)
		float characterHealth;
	//UFUNCTIONS
	UFUNCTION(BlueprintCallable)
		void OnHitByBullet(float bulletDamage);
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

};
