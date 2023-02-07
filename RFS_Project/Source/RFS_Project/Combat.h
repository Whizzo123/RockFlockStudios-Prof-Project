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
	virtual void OnDeath() = 0;
};
