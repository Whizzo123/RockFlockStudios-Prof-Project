// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARestrictedCamera.h"
#include "UShadowWall.h"
#include "Ability.h"
#include "IShadowPawn.h"
#include "PlayerCharacter.h"
#include "BaseShadowAbility.generated.h"



//Comment in regards to caller
	/**
	 * Called when player attempts to use ability
	 * @param OutFocusMultiplier - Upon return, will contain a multiplier to apply to the drinker's focus.
	 * @note OutThirstQuenchingFraction - Upon return, will contain the fraction of the drinker's thirst to quench (0-1).
	 * @warning Only call this after the drink has been properly prepared.
	 * @see Only call this after the drink has been properly prepared.
	 * @return
	 */

//Public implementation first, then private implementation

/*An Abstract Class for the Shadow Ultimate Ability. Iterations of this ability must inherit from here*/
UCLASS(Abstract)
class RFS_PROJECT_API UBaseShadowAbility : public UActorComponent, public IAbility
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:	
	UBaseShadowAbility();
	/**
	* Sets our Original Pawn for later: repossess when exiting Walls. 
	* @note: THE ACTOR MUST HAVE ISHADOWPAWN INTERFACE
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void Init(APawn* SelfActor)
	{
		bool bImplementsShadowPawn = UKismetSystemLibrary::DoesImplementInterface(SelfActor, UShadowPawn::StaticClass());
		if (bImplementsShadowPawn)
		{
			OriginalActor = SelfActor;
		}
		else 
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::Init() SelfActor is either null or does not implement IShadowPawn"));
		}
	};

	/**
	* Called when player attempts to use ability
	*/
	virtual bool Use_Implementation() override;

	/**
	 * Adds a Use until it reaches capacity
	 */
	virtual void AddUse_Implementation() override
	{
		if (UseData.Use < UseData.UseCapacity)
		{
			UseData.Use++;
		}
	};
	/**
	 * Reduces use by amount. If the subtraction leads to a negative number, Use is set to 0.
	 */
	virtual void SubtractUse_Implementation(int Amount) override
	{
		if (UseData.Use < 0 && UseData.Use >= Amount)
		{
			UseData.Use -= Amount;
		}
		else
		{
			UseData.Use = 0;
		}
	};
	/**
	 * Adds a Charge till it reaches Capacity, automatically adds a Use once ChargeCapacity is reached
	 */
	virtual void AddCharge_Implementation() override
	{
		//Add a charge till full, add a use on full charge
		if (UseData.Charge < UseData.ChargeCapacity)
		{
			UseData.Charge++;
			//Add use if charge is full
			if (UseData.Charge >= UseData.ChargeCapacity)
			{
				IAbility::Execute_AddUse(this);
				//Can call DepleteCharge() here if there are multiple uses
			}
		}

	};
	/**
	 * Reduces Charge to 0
	 */
	virtual void DepleteCharge_Implementation()override
	{
		UseData.Charge = 0;
	};


	/**
	* Gets the amount of walls currently active with the ability
	*/
	UFUNCTION(BlueprintCallable)
		int GetAliveWallCount() 
	{
		return AliveWalls.Num();
	};
	/**
	* Gets the array of the Alive Walls Set
	* @return Array if aliveWalls
	*/
	UFUNCTION(BlueprintCallable)
		TArray<AUShadowWall*> GetAliveWallArray() {
		if (AliveWalls.Num() > 0)
		{
			return AliveWalls.Array();
		}
		else 
		{
			return TArray<AUShadowWall*>();
		}
	};
	/**
	* Gets the CurrentWall identifier inside the AliveWall array
	* @return AliveWall[identifier] where identifier should equal current wall's position
	* @note Will return -1 if wall doesn't exist in array or AliveWall has no elements
	*/
	UFUNCTION(BlueprintCallable)
		int GetCurrentWallIdentifierInContextOfArray() {
		TArray<AUShadowWall*> Walls = GetAliveWallArray();
		//Finds CurrentWall in array
		for (int i = 0; i < Walls.Num(); i++)
		{
			if (Walls[i] == CurrentWall)
			{
				return i;
			}
		}
		return -1;
	}
	/**
	* Gets the main wall that if destroyed, will collapse all walls. Usually the wall that the player is inside.
	* @note Will return a nullptr if CurrentWall does not exist.
	*/
	UFUNCTION(BlueprintCallable)
		AUShadowWall* GetCurrentWall() {
		if (IsValid(CurrentWall))
		{
			return CurrentWall;
		}
		else 
		{
			return nullptr;
		}
	}

	UFUNCTION(BlueprintCallable)
		virtual void AbortAll();
	//BLUEPRINT IMPLEMENTABLE EVENTS
	/**
	* Gets called when we are cueing the ability
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_CueAbility();
	/**
	* Gets called when we succeed the Cue State
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_InitAbility();	
	/**
	* Gets called when we Enter the Wall
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_EnterWall();	
	/**
	* Gets called when we Exit the Wall
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_ExitWall();
	/**
	* Gets called when we succeed the ability ends and walls come down
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_EndAbility();
	/**
	* Gets called when we succeed the ability ends and walls come down
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_EndAbilityTime();
	/**
	* Gets called a fake wall is destroyed
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_FakeWallDestroyed();	
	/**
	* Gets called the CurrentWall is destroyed and we endability abruptly
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
		void BPI_RealWallDestroyed();
	//MEMBER VARIABLES
		/**
		* The current state of the ability
		*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		EAbilityState ShadowState;
	/*Contains Charge and Use with Capacities for ability usage*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		FAbilityData UseData;
		/*Amount of walls to turn on, including the original wall we looked at. Limited by how many VFX walls we can activate(4)*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		int WallAmount = 4;
		/*Range we can cast to, 300 - max range*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float Range = 2000.0f;
		/*Range of wall detection, 300 - max range*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float WallDetectionRange = 2000.0f;
		/*Accuracy of wall detection, 10 - 360 range*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		int DiscAccuracy = 360;
		/*Duration of the ability, 5 - max range*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float Duration = 20.0f;
		/*Duration of the ability when we exit the walls, 0 - max range*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Parameters")
		float DurationEndStart = 3.0f;
		/*Timer of the ability duration, at 0 ability will end automatically*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability Parameters")
		float DurationTimer;

		/*The Actor BP to Spawn and possess when we enter walls*/
	UPROPERTY(EditDefaultsOnly, Category = "Ability BP Actors")
		TSubclassOf<AARestrictedCamera> RestrictedActorBP;
	/*Wall Actor we possess reference*/
	AARestrictedCamera* RestrictedActor;

	/*Boolean required to specifiy the VFX walls for AI Omen Ability*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsPlayerAbility = true;
	/*Whether we are inside the walls or not*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		bool bInsideWalls = false;
protected:
	//HELPER FUNCTIONS
	/**
	* If Actor contains a camera component, grabs the camera's forward vector. Otherwise grabs actors forward vector.
	* @return Camera Forward Vector | Actor Forward Vector
	*/
	FVector GetCameraActorForwardVector(AActor* ActorFwd);
	/**
	* Tries to Destroy() actor, otherwise teleports and set the actor to hidden
	*/
	void DestroyOrHideActor(AActor* actor);

	//STATE FUNCTIONS
	/**
	* What to do when Use is called in Inactive state
	*/
	virtual bool InactiveState() { return false; };
	/**
	* What to do when Use is called in Cue state
	*/
	virtual bool CueState() { return false; };
	/**
	* What to do when Use is called in Active state
	*/
	virtual bool ActiveState() { return false; };

	//ABILITY IMPLEMENTATION FUNCTIONS
	/**
	* Grabs all AUShadowWalls within a sphere around the origin point
	* @return Camera Forward Vector | Actor Forward Vector
	* @deprecated This is a depreciated function, we no longer want to grab walls on top or below
	*/
	TSet<AUShadowWall*> SphereCastWalls(FVector origin, float Range);
	/**
	* Grabs all AUShadowWalls within a horizontal 360 disc around Origin
	* @return All inactive walls will be returned.
	*/
	TSet<AUShadowWall*> DiscCastWalls(FVector Origin);
	/**
	* Grabs unused and currently inactive walls.
	* @return 'WallAmount' of AUShadowWalls
	*/
	TSet<AUShadowWall*> ChooseWalls(TSet<AUShadowWall*> walls);
	/*
	*Turns on walls with ID's and play bool
	*/
	void TurnOnWalls();
	/*
	*Displays walls around player. Updates every (FixedTime) seconds.
	*/
	void CueWallVisible(float DeltaTime);
	/*
	*Turns off all visible Cue Walls
	*/
	void TurnOffVisibleWalls();
	/**
	* Reposses the Original Actor and destroys the old actor
	* @return true if we have successfully completed the operation
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability Callable")
		bool EnterWall(AUShadowWall* WallToEnter);
	/**
	* Reposses the Original Actor and destroys the old actor
	* @return true if we have successfully completed the operation
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability Callable")
		bool ExitWall();
	/**
	* Ends walls and resets parameters
	*/
	virtual void EndAbility();

	virtual void EndAbilityAbrupt();

	void UpdateAliveWalls();
	void AbilityTickResponse(float DeltaTime);
	/*The Actor we want to repossess when exiting walls*/
	APawn* OriginalActor;
	/*The walls that activate when we use ability*/
	TSet<AUShadowWall*> AliveWalls;
	/*Designated main wall, usually the wall that the player is in*/
	AUShadowWall* CurrentWall;

private:
	void AdvanceState();
	TSet<AUShadowWall*> GetValidWallsFromHits(TArray<FHitResult> Hits);
	const float CueWallFixedTime = 3.0f;
	float CueWallFixedTimeChange = 0.0f;
	TSet<AUShadowWall*> VisibleWalls;

};
