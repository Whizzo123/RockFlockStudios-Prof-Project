// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class IHealth
{
public:
	virtual void OnHeal(float health) = 0;
	virtual void OnDamage(float damage) = 0;
	virtual void OnDeath() = 0;
};