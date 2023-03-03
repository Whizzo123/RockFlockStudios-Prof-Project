// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Base AbilityClass
 */
class RFS_PROJECT_API IAbility
{
public:
	virtual void Init(APawn* SelfActor) = 0;
	virtual void Use() = 0;
	
};