// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
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
	virtual void OnHeal(float health) = 0;
	virtual void OnDamage(float damage, AActor* actorReceivedDamageFrom) = 0;
	virtual void OnDeath() = 0;
	virtual void OnKill() = 0;
};
