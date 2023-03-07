// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "IShadowPawn.h"
#include "../Combat.h"
#include "PlayerCharacter.generated.h"





UCLASS()
class RFS_PROJECT_API APlayerCharacter : public APlayableCharacter, public IShadowPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	//UPROPERTIES
	UPROPERTY(EditAnywhere)
		float characterHealth;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIHint, AActor*, Player, float, hintTime);
	FAIHint OnAIHint;
	//UFUNCTIONS
	UFUNCTION(BlueprintCallable)
		void OnHitByBullet(float bulletDamage);
	UFUNCTION(BlueprintCallable)
		void CreateHint();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnHeal(float health) override;
	void OnDamage(float damage) override;
	void OnDeath() override;
	FVector respawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
