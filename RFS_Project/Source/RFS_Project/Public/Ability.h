// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
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
	//UFUNCTION(BlueprintCallable, Category = "Ability") //Should have this UFUNCTION Specifier

			virtual bool Use() = 0;

		//Setters
			virtual void AddUse() = 0;
			virtual void DepleteUse() = 0;
			virtual void AddCharge() = 0;
			virtual void DepleteCharge() = 0;

		//Getters
			virtual int GetUseAmount() = 0;
			virtual int GetUseCapacity() = 0;
			virtual int GetChargeAmount() = 0;
			virtual int GetChargeCapacity() = 0;

};

UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	Inactive UMETA(DisplayName = "Inactive"),
	Cue UMETA(DisplayName = "Cue"),
	Active UMETA(DisplayName = "Active"),
};

USTRUCT(BlueprintType)
struct FAbilityData {
	GENERATED_BODY()
public:
	//////////////////////BASE ABILITY FUNCTIONALITY
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Uses")
		int Use;//Current amount of ability usages that can be used.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Uses")
		int UseCapacity;//How many ability usages can be stored.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Charge")
		int Charge;//The ultimate charge counter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Charge")
		int ChargeCapacity;//Ultimate charge capacity, once full, ability can be used.
};

