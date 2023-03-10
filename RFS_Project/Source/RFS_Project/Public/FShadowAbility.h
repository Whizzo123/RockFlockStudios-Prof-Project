// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UShadowWall.h"
#include "ShadowPortal.h"
#include "Math/UnrealMathUtility.h"
#include "ARestrictedCamera.h"
#include "Ability.h"
#include "FShadowAbility.generated.h"

//class AUShadowWall;
//class AUShadowEntrence;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class RFS_PROJECT_API UFShadowAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFShadowAbility();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UseAbility();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void Init(APawn* SelfActor);

private:
	bool InitAbility(FVector position, FVector fwdVector);
	bool PlacePortal(FVector position, FVector fwdVector);
	TSet<AUShadowWall*> SphereCastWalls(FVector origin);
	TSet<AUShadowWall*> ChooseWalls(TSet<AUShadowWall*> walls);
	
	bool EnterPortal();

	bool ExitWall();
	void DestroyOrHideActor(AActor* actor);
	void EndAbility();
	void TogglePortalUseable() { bPortalUseable = !bPortalUseable; };

public:
	//////////////////////BASE ABILITY FUNCTIONALITY
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		int UseAmount;//Current amount of ability usages that can be used.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		int UseCapacity;//How many ability usages can be stored.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		int ChargeAmount;//The ultimate charge counter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		int ChargeCapacity;//Ultimate charge capacity, once full, ability can be used.
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
		/// Adds a charge, if you reach the max charge, deplete all charges and add a use.
		/// </summary>
		void AddCharge() { 
		if (ChargeAmount < ChargeCapacity)
			ChargeAmount++;
		if (ChargeAmount >= ChargeCapacity && UseAmount < UseCapacity) {
			AddUse();
			//DepleteCharge();
		}

	}		
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
	/// Adds a Use up to the max use amount
	/// </summary>
		void AddUse() {
		UseAmount++; 
		if (UseAmount > UseCapacity)
			UseAmount = UseCapacity;
	}
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void DepleteCharge() { ChargeAmount = 0; }
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void DepleteUse() { UseAmount= 0; }

	///////////////////////////ShadowAbility Parameters
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		int WallAmount = 4;//The amount of walls to enable, including our target
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float Range = 2000.0f;//The range of our casting
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float SphereRange = 2000.0f;//The range to grab walls
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float Duration = 20.0f;//The initial duration of the ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float DurationMultiplier = 1.5f;//How much time should be multiplied on from the current duration when entering the portal
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float DurationEndStart = 3.0f;//When the player exits the portal, how much longer should walls stay
	UPROPERTY(BlueprintReadOnly, Category = "Ability Parameters")
		float DurationTimer;//The current time of the ability in use

	/*Blueprint Reference of UsefulActor class*/
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AShadowPortal> PortalBP;	
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AARestrictedCamera> RestrictedActorBP;

	UPROPERTY(BlueprintReadOnly, Category = "Ability States")
		bool bActivated = false;
	UPROPERTY(BlueprintReadOnly, Category = "Ability States")
		bool bEnteredPortal = false;
	UPROPERTY(BlueprintReadOnly, Category = "Ability States")
		bool bExitedPortal = false;
	UPROPERTY(BlueprintReadOnly, Category = "Ability States")
		bool bPortalUseable = false;
private:
	APawn* OriginalActor;
	AARestrictedCamera* RestrictedActor;


	TSet<AUShadowWall*> AliveWalls;
	AShadowPortal* Portal;
	AUShadowWall* PortalWall;
};