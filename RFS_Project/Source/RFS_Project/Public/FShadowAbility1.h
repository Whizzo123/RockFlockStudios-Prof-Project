// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "BaseShadowAbility.h"
#include "Math/UnrealMathUtility.h"
#include "FShadowAbility1.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class RFS_PROJECT_API UFShadowAbility1 : public UBaseShadowAbility
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFShadowAbility1();
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* Teleport the player between the walls that are currently alive
	* @return Charge Capacity
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool SwitchWalls(int WallID);

	/**
* Teleport the player between the walls that are currently alive
* @return Charge Capacity
*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool GoIntoWall();
private:
	bool InactiveState() override;
	bool CueState() override;
	bool ActiveState() override;


	/**
	* Calls functions in order: PlacePortal(...), DiscCastWalls(...), ChooseWalls(...), then turns them on.
	* @return true if all succeed.
	*/
	bool InitAbility(FVector position);


private:


};
