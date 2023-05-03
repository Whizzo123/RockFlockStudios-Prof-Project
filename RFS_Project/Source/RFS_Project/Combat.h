// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Combat.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class RFS_PROJECT_API IHealth
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
		void OnHeal(float Health);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void BPI_OnHeal(float Health);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
		void OnDamage(float Damage, AActor* ActorReceivedDamageFrom);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void BPI_OnDamage(float Damage, AActor* ActorReceivedDamageFrom);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
		void OnDeath();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void BPI_OnDeath();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
		void OnKill();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void BPI_OnKill();
};
