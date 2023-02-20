// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RFS_PROJECT_API IHealth
{
public:
	IHealth() {};
	float HitPoints;
	float MaxHitPoints;
	virtual void OnHeal(float health) = 0;
	virtual void OnDamage(float damage) = 0;
	virtual void OnDeath() = 0;
};
