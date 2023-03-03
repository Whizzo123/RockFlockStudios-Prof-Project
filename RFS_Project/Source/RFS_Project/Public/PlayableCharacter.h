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
		UPROPERTY(EditAnywhere, Category="Combat")
		float HitPoints;
		UPROPERTY(EditAnywhere, Category="Combat")
		float MaxHitPoints;
	// Sets default values for this actor's properties
		UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
	void OnHeal(float health) override {};
		UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
			void OnDamage(float damage) override {};
		UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
			void OnDeath() override {};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayableCharacter();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};