// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class RFS_PROJECT_API IAbility
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		bool Use();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		void AddUse();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		void SubtractUse(int Amount);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		void AddCharge();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
		void DepleteCharge();

};

UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	Inactive UMETA(DisplayName = "Inactive"),
	Cue UMETA(DisplayName = "Cue"),
	Active UMETA(DisplayName = "Active"),
};

/*Struct containing Valorant's Ultimate charging and usage system*/
USTRUCT(BlueprintType)
struct FAbilityData {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data")
		int Use;//Current amount of ability usages that can be used.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data")
		int UseCapacity;//How many ability usages can be stored.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data")
		int Charge;//The ultimate charge counter.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data")
		int ChargeCapacity;//Ultimate charge capacity, once full, ability can be used.
};

