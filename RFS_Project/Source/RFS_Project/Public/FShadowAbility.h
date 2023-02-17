// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UShadowWall.h"
#include "Ability.h"
#include "FShadowAbility.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void Use() override;

	UPROPERTY(EditAnywhere)
		float AbilityRange = 500.0f;
	UPROPERTY(EditAnywhere)
		int TraceAmounts = 10;//This determines how many line traces get sent. Alter for accuracy and performance.

private:
	void GetWalls();
	void SpawnPortals();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

};