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

			virtual void Use() = 0;

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
enum EAbilityState
{
	Inactive UMETA(DisplayName = "Inactive"),
	Cue UMETA(DisplayName = "Cue"),
	Active UMETA(DisplayName = "Active"),
};
USTRUCT()
struct FAbilityData {
	GENERATED_BODY()
public:
	int Charge;
	int ChargeCapacity;
	int Use;
	int UseCapacity;
};

