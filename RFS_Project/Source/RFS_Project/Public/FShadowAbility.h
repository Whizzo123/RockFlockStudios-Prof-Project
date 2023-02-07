// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FShadowAbility.generated.h"
#include "UShadowWall.h"
#include "Ability.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RFS_PROJECT_API UFShadowAbility : public UActorComponent, public IRechargeAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFShadowAbility();
	TArray<AUShadowWall*> FakeWalls;
	AUShadowEntrence* ShadowEntrence;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void Use() override;
	void SpawnPortals();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
