// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/Class.h"
#include "ShadowPortal.h"
#include "BaseShadowAbility.h"
#include "Math/UnrealMathUtility.h"
#include "FShadowAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
/*Shadow Ability Version 1, Portal Entry, No teleporting, same entry exit*/
class RFS_PROJECT_API UFShadowAbility : public UBaseShadowAbility
{
	GENERATED_BODY()

public:
	UFShadowAbility();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	bool Use() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float DurationMultiplier = 1.5f;//How much time should be multiplied on from the current duration when entering the portal
	UPROPERTY(EditDefaultsOnly, Category = "Ability BP Actors")
		TSubclassOf<AShadowPortal> PortalBP;//The Portal in BP's	
	UPROPERTY(EditAnywhere, Category = "Fake Portal Material")
		UMaterialInterface* RedMaterial;//Red Material for the portal
	UPROPERTY(EditAnywhere, Category = "Fake Portal Material")
		UMaterialInterface* GreenMaterial;//Green material for the portal


	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		bool bWithinPortalRange = false;
	/*Whether we are inside the walls or not*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		bool bInsideWalls = false;
private:
	bool InactiveState() override;
	bool CueState() override;
	bool ActiveState() override;

	bool EnteredState();

	/**
	* Calls functions in order: PlacePortal(...), DiscCastWalls(...), ChooseWalls(...), then turns them on.
	* @return true if all succeed.
	*/
	bool InitAbility(FVector position, FVector fwdVector);
	/**
	* Calls functions in order: PlacePortal(...), DiscCastWalls(...), ChooseWalls(...), then turns them on.
	* @return true if all succeed.
	*/
	bool PlacePortal(FVector position, FVector fwdVector);
	/**
	* Updates the position of the fake portal, turning it green when on a AUShadowWall, red otherwise.
	* @note Rotates the rotation of the plane based on the normal it is hitting.
	*/
	void UpdateFakePortal(FVector position, FVector fwdVector);
	/**
	* Ends walls, portals, and resets parameters
	*/
	void EndAbility() override;
	void TogglePortalUseable() { bWithinPortalRange = !bWithinPortalRange; };


private:
	AShadowPortal* Portal;
	AUShadowWall* PortalWall;



};