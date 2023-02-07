// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Combat.h"
#include "UShadowWall.generated.h"

UCLASS()
class RFS_PROJECT_API AUShadowWall : public AActor, public IHealth
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUShadowWall(int WSize) { Size = WSize; };
	UObject* AttachedWall;
	int Size;
	void Spawn();
	void OnDeath() override;//TODO health ovveride;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


UCLASS()
class RFS_PROJECT_API AUShadowEntrence : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUShadowEntrence(int wSize) { bContainsPlayer = false; Size = WSize; };
	bool bContainsPlayer;

	UObject* AttachedWall;
	int Size;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};



