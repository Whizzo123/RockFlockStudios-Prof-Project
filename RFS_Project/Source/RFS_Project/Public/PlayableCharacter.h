// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Combat.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class RFS_PROJECT_API APlayableCharacter : public ACharacter, public IHealth
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	void OnHeal(float health) override {};
	void OnDamage(float damage) override {};
	void OnDeath() override {};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayableCharacter();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
