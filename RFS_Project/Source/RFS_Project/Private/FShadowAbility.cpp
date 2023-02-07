// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility.h"

// Sets default values for this component's properties
UFShadowAbility::UFShadowAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UseAmount = 1;
	UseCapacity = 1;
	ChargeAmount = 7;
	ChargeCapacity = 7;
	// ...
}


// Called when the game starts
void UFShadowAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFShadowAbility::Use()
{
	if (UseAmount <= 0)
		return;

	UseAmount--;
	
	//Use Ability
	SpawnPortals();
}

void UFShadowAbility::SpawnPortals()
{

}


// Called every frame
void UFShadowAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

