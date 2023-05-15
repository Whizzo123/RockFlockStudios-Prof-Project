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
	* Character increases HitPoints by amount
	* @param Health - Amount to heal the character by
	*/
	void OnHeal_Implementation(float Health) override;
	/*
	* Damage player by amount and by actor damaged by
	* @param Damage - Amount to damage character by
	* @param ActorDamagedBy - Actor responsible for the damage
	*/
	void OnDamage_Implementation(float Damage, AActor* ActorDamagedBy) override;

	/* Character has killed something*/
	void OnKill_Implementation() override;
	/*Character has died*/
	virtual void OnDeath_Implementation() override;
	/*Blueprint-implementable event for when the character fires they're gun*/
	UFUNCTION(BlueprintImplementableEvent)
		void OnGunFire();
	/*Blueprint-implementable event for when the character stops firing they're gun*/
	UFUNCTION(BlueprintImplementableEvent)
		void OnGunFiringStopped();


	/* Plays the characters reload animation*/
	void PlayReloadAnimation();
	/* Value for amount of hit points the character currently has*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
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
	AActor* SavedActorDamageBy;
private:
	FVector RespawnPoint;

};
