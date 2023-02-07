// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Base AbilityClass
 */
class RFS_PROJECT_API IAbility
{
public:
	virtual void Use() = 0;
};

/// <summary>
/// Practically for any normal ability
/// </summary>
class RFS_PROJECT_API ISingleUseAbility : public IAbility
{
public:
	ISingleUseAbility() {};
	~ISingleUseAbility() {};

	virtual void Use() = 0;
	int GetUseAmount() { return UseAmount; }
	int GetUseCapacity() { return UseCapacity; }
private:
	int UseAmount;//Current amount of ability usages that can be used.
	int UseCapacity;//How many ability usages can be stored.
};

/// <summary>
/// For ultimate abilities
/// </summary>
class RFS_PROJECT_API IRechargeAbility : public ISingleUseAbility
{
public:
	IRechargeAbility() {};
	~IRechargeAbility() {};

	virtual void Use() = 0;
	int GetChargeAmount() { return ChargeAmount; }
	int GetChargeCapacity() { return ChargeCapacity; }
private:
	int ChargeAmount;//The ultimate charge counter
	int ChargeCapacity;//Ultimate charge capacity, once full, ability can be used.
};
