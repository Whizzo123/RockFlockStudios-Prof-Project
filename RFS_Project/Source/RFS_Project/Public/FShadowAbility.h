// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/Class.h"
#include "UShadowWall.h"
#include "ShadowPortal.h"
#include "Math/UnrealMathUtility.h"
#include "ARestrictedCamera.h"
#include "FShadowAbility.generated.h"

//class AUShadowWall;
//class AUShadowEntrence;
UENUM(BlueprintType)
enum AbilityState
{
	Inactive UMETA(DisplayName = "Inactive"),
	Cue UMETA(DisplayName="Cue"),
	Active UMETA(DisplayName="Active"),
	Entered UMETA(DisplayName="Entered"),
};

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
		/// <summary>
		/// Base function to call, same button press will advance the state machine of the ability
		/// </summary>
		void UseAbility();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		/// <summary>
		/// Function needed to call before using the ability. sets data
		/// </summary>
		void Init(APawn* SelfActor);

	UFUNCTION(BlueprintCallable, Category = "Ability Callable")
		/// <summary>
		/// Places portal, grabs and activates x walls.
		/// </summary>
		bool InitAbility(FVector position, FVector fwdVector);
	UFUNCTION(BlueprintCallable, Category = "Ability Callable")
		/// <summary>
		/// If bPortalUsable is true we can enter the portal. Possess new actor and hides OriginalActor
		/// </summary>
		bool EnterPortal();


	UFUNCTION(BlueprintImplementableEvent)
		void BPI_AbilityEnter();		
	UFUNCTION(BlueprintImplementableEvent)
		void BPI_AbilityExit();	
	UFUNCTION(BlueprintImplementableEvent)
		void BPI_AbilityEnd();	
	UFUNCTION(BlueprintImplementableEvent)
		void BPI_AbilityCue();	
	UFUNCTION(BlueprintImplementableEvent)
		void BPI_AbilityStart();

private:
	bool InactiveState();
	bool CueState();
	bool ActiveState();
	bool EnteredState();
	/// <summary>
	/// Places portal
	/// </summary>
	bool PlacePortal(FVector position, FVector fwdVector);
	/// <summary>
	/// Updates the fake portal that we can see before we confirm ability usage
	/// </summary>
	void UpdateFakeWall(FVector position, FVector fwdVector);
	/// <summary>
	/// Gets OriginalActor forward vector
	/// </summary>
	FVector GetOriginalActorForwardVector();
	/// <summary>
	/// Grabs walls in a sphere around portal point
	/// </summary>
	TSet<AUShadowWall*> SphereCastWalls(FVector origin);
	/// <summary>
	/// Grabs walls in a horizontal disc around portal point
	/// </summary>
	TSet<AUShadowWall*> DiscCastWalls(FVector origin);
	/// <summary>
	/// Grabs random walls to use
	/// </summary>
	TSet<AUShadowWall*> ChooseWalls(TSet<AUShadowWall*> walls);
	
	/// <summary>
	/// Repossess the OriginalActor and destroys old actor
	/// </summary>
	bool ExitWall();
	/// <summary>
	/// Attempts to Destroy actor, otherwise hides it
	/// </summary>
	void DestroyOrHideActor(AActor* actor);
	/// <summary>
	/// Ends the ability, keeping in mind the current state
	/// </summary>
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
		float WallDetectionRange = 2000.0f;//The range to grab walls	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		int DiscAccuracy = 360;//The range to grab walls
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
		TSubclassOf<AShadowPortal> PortalBP;//The Portal in BP's	
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AARestrictedCamera> RestrictedActorBP;// The actor to be inside the wall BP's
	UPROPERTY(EditAnywhere, Category = "Fake Portal Material")
		UMaterialInterface* RedMaterial;//Red Material for the portal
	UPROPERTY(EditAnywhere, Category = "Fake Portal Material")
		UMaterialInterface* GreenMaterial;//Green material for the portal


	UPROPERTY(BlueprintReadWrite, Category = "Ability States")
		bool bPortalUseable = false;
	bool bPortalPlaceable = false;

	UPROPERTY(BlueprintReadOnly, Category = "Ability State")
		TEnumAsByte<AbilityState> State;//The current state of the ability
private:
	APawn* OriginalActor;
	AARestrictedCamera* RestrictedActor;


	TSet<AUShadowWall*> AliveWalls;
	AShadowPortal* Portal;
	AUShadowWall* PortalWall;

};