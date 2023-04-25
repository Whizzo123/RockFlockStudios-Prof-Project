// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "../Combat.h"
#include "UShadowWall.generated.h"


UCLASS()
class RFS_PROJECT_API AUShadowWall : public AActor, public IHealth
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUShadowWall();
	~AUShadowWall() {};
	void Spawn();

	UPROPERTY(EditAnywhere, Category = "Combat")
		float HitPoints;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float MaxHitPoints;
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnDamage(float damage, AActor* actorDamagedBy) override { 
		if (bAlive)
		{
			HitPoints -= damage;
			if (HitPoints < 0)
			{
				OnDeath();
				bAlive = false;
				if (!bISPlayerInside)
				{
					BPI_FlashActor(actorDamagedBy);
				}
			}
		}

	};
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnHeal(float heal) override {
		if (bAlive)
		{
			HitPoints += heal;
			if (HitPoints > MaxHitPoints)
			{
				HitPoints = MaxHitPoints;
			}
		}

	};
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void OnDeath() override { BPI_OnDeath(); };

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
		void BPI_OnDeath();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BPI_FlashActor(AActor* actor);


	void OnKill() override {};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartWall(int i, bool Player);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeWallTextures(int i, bool Player);


	UFUNCTION(BlueprintCallable)
	void ResetWall();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WallPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bISPlayerInside = false;
};


