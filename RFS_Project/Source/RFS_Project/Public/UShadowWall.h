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
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnDamage(float Damage, AActor* ActorDamagedBy) override;
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combat")
		void OnHeal(float heal) override;
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void OnDeath() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
		void BPI_OnDeath();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BPI_FlashActor(AActor* actor);


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BPI_SparksDamage();

	void OnKill() override {};
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


