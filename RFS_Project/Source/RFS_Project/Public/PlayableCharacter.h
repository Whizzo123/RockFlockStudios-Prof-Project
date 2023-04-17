// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Combat.h"
#include "PlayableCharacter.generated.h"

UCLASS()
/*A class for the base functionality of characters within the game*/
class RFS_PROJECT_API APlayableCharacter : public ACharacter, public IHealth
{
	GENERATED_BODY()
	
public:	
	/*
	* Called every frame
	* @param DeltaTime - Time between frames
	*/
	virtual void Tick(float DeltaTime) override;
	/*
	* Blueprint-callable function for healing the character
	* @param Health - Amount to heal the character by
	*/
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnHeal(float Health) override {};
	/*
	* Blueprint-callable function for damaging the character
	* @param Damage - Amount to damage character by
	* @param ActorDamagedBy - Actor responsible for the damage
	*/
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnDamage(float Damage, AActor* ActorDamagedBy) override {};
	/*Blueprint-callable function for when the player should die*/
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnDeath() override {};
	/*Blueprint-implementable event for when the character fires they're gun*/
	UFUNCTION(BlueprintImplementableEvent)
		void OnGunFire();
	/*Blueprint-implementable event for when the character stops firing they're gun*/
	UFUNCTION(BlueprintImplementableEvent)
		void OnGunFiringStopped();
	/*
	* Blueprint-implementable event for when the character takes damage
	* @param ActorDamagedBy - The actor who damaged us
	*/
	UFUNCTION(BlueprintImplementableEvent)
		void CharacterDamagedEvent(AActor* ActorDamagedBy);

	UFUNCTION(BlueprintImplementableEvent)
		void BPI_OnDeath();
	/* Kills the character*/
	void OnKill() override {};

	/* Plays the characters reload animation*/
	void PlayReloadAnimation();
public:
	/* Value for amount of hit points the character currently has*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
		float HitPoints;
	/*Value for max amount of hit points character can have*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
		float MaxHitPoints;
	/*Animation to play on reload*/
	UPROPERTY(EditAnywhere)
		UAnimSequence* ReloadAnim;
protected:
	/*Called when game starts or actor is spawned*/
	virtual void BeginPlay() override;
	/*Default constructor*/
	APlayableCharacter();
};
