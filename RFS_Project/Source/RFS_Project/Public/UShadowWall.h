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
protected:
	virtual void BeginPlay() override;
public:
	AUShadowWall();
	~AUShadowWall() {};
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float HitPoints;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float MaxHitPoints;
		void OnHeal_Implementation(float heal) override;
		void OnDamage_Implementation(float Damage, AActor* ActorDamagedBy) override;
		void OnDeath_Implementation() override;
		void OnKill_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BPI_FlashActor(AActor* actor);

	void EndWall();

	UFUNCTION(BlueprintCallable)
	void StartWall(int i, bool Player, AActor* NewOwner);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeWallTextures(int i, bool Player);

	void ChangeVisibility(bool Visible);

	UFUNCTION(BlueprintCallable)
		bool IsAlive() {
		if (HitPoints >= 0)
		{
			return true;
		}
		return false;
	}
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WallPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bISPlayerInside = false;

private:
	AActor* OwningPlayer;
};


