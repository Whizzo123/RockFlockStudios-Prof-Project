// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.h"
#include "BaseShadowAbility.generated.h"

UCLASS(Abstract, NotBlueprintable)
class RFS_PROJECT_API UBaseShadowAbility : public UActorComponent, public IAbility
{
	GENERATED_BODY()



public:	
	UBaseShadowAbility();

		/// <summary>
		/// To be implemented
		/// </summary>
	virtual void Use() override {};

	//Setters
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
		/// Adds a Use till Capacity. Once at Capacity, adds a Charge automatically.
		/// </summary>
		virtual void AddUse() override {

		UseData.Use++;
		if (UseData.Use > UseData.UseCapacity)
			UseData.Use = UseData.UseCapacity;
	};
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
		/// Depletes Use only, not Charge
		/// </summary>
		virtual void DepleteUse() override {
		UseData.Use = 0;
	};
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
		/// Adds a Charge up till ChargeCapacity
		/// </summary>
		virtual void AddCharge() override {
		//Add a charge till full, add a use on full charge
		if (UseData.Charge < UseData.ChargeCapacity)
			UseData.Charge++;
		if (UseData.Charge >= UseData.ChargeCapacity && UseData.Use < UseData.UseCapacity) {
			AddUse();
			//DepleteCharge(); // This was to only be in for multiple use cases.
		}
	};
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
		/// Depletes Charge only, not Use
		/// </summary>
		virtual void DepleteCharge()override {
		UseData.Charge = 0;
	};

	//Getters
	UFUNCTION(BlueprintCallable, Category = "Ability")
		virtual int GetUseAmount()override {
		return UseData.Use;
	};
	UFUNCTION(BlueprintCallable, Category = "Ability")
		virtual int GetUseCapacity()override {
		return UseData.UseCapacity;
	};
	UFUNCTION(BlueprintCallable, Category = "Ability")
		virtual int GetChargeAmount() override {
		return UseData.Charge;
	};
	UFUNCTION(BlueprintCallable, Category = "Ability")
		virtual int GetChargeCapacity() override {
		return UseData.ChargeCapacity;
	};

	FAbilityData UseData;
	EAbilityState ShadowState;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
