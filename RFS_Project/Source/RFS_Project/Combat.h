// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat.generated.h"
/**
 * 
 */
UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class RFS_PROJECT_API UHealth : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

inline UHealth::UHealth(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

class IHealth
{
	GENERATED_IINTERFACE_BODY()
public:

	float HitPoints;
	float MaxHitPoints;
	virtual void OnHeal(float health) = 0;
	virtual void OnDamage(float damage) = 0;
	virtual void OnDeath() = 0;
};

