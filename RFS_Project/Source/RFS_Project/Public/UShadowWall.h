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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartWall(int i, bool Player, AActor* NewOwner);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeWallTextures(int i, bool Player);

	void ChangeVisibility(bool Visible);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WallPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bISPlayerInside = false;

private:
	AActor* OwningPlayer;
};


