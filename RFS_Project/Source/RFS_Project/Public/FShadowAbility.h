// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UShadowWall.h"
#include "ShadowPortal.h"
#include "Ability.h"
#include "FShadowAbility.generated.h"

//class AUShadowWall;
//class AUShadowEntrence;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RFS_PROJECT_API UFShadowAbility : public UActorComponent, public IRechargeAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFShadowAbility();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void Use() override;
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void Init(APawn* actor) override;

private:
	bool InitAbility(FVector position, FVector fwdVector);
	bool PlacePortal(FVector position, FVector fwdVector);
	void GetWalls();
	void SpawnPortals();
	void ExitWall();
	void EndAbility();
	void TogglePortalUseable() { bPortalUseable = !bPortalUseable; };
public:
	// Called every frame


	UPROPERTY(EditAnywhere)
		int WallAmount = 3;
	UPROPERTY(EditAnywhere)
		float Range = 2000.0f;
	UPROPERTY(EditAnywhere)
		float SphereRange = 2000.0f;
	UPROPERTY(EditAnywhere)
		float Duration = 20.0f;
	UPROPERTY(EditAnywhere)
		float DurationMultiplier = 1.5f;
	UPROPERTY(EditAnywhere)
		float DurationEndStart = 3.0f;


private:
	APawn* OriginalActor;
	float DurationTimer;
	bool bActivated;
	bool bEnteredPortal;
	bool bExitedPortal;
	bool bPortalUseable;

	TArray<AUShadowWall*> AliveWalls;
	AShadowPortal* Portal;
	AUShadowWall* PortalWall;
};