// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility1.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility.h"

// Sets default values for this component's properties
UFShadowAbility1::UFShadowAbility1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ShadowState = EAbilityState::Inactive;
	// ...
}


// Called when the game starts
void UFShadowAbility1::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Starting Shadow Ability"));
	// ...

}

#pragma region STATE_FUNCTIONS

bool UFShadowAbility1::GoIntoWall()
{
	if (ShadowState != EAbilityState::Active)
	{
		return false;
	}
	bool bSuccess = EnterWall(CurrentWall);
	if (!bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Couldn't enter wall"));
		return false;
	}
	return true;
}

bool UFShadowAbility1::InactiveState() {
	//Do we have uses
	if (UseData.Use <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Out of Ability Uses"));
		return false;
	}

	BPI_CueAbility();//Should Play animation for cueing the ability
	return true;
}
bool UFShadowAbility1::CueState() 
{
	TurnOffVisibleWalls();

	FVector Location = OriginalActor->GetActorLocation();
	bool bSuccess = InitAbility(Location);
	if (!bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));
		return false;
	}
	else
	{
		//Try to enter a wall
		CurrentWall = AliveWalls.Array()[0];
		
		//Start ability data
		DurationTimer = Duration;
		IAbility::Execute_SubtractUse(this, 1);
		IAbility::Execute_DepleteCharge(this);
		
		BPI_InitAbility();
		return true;
	}
}
bool UFShadowAbility1::ActiveState() {
	bool success = ExitWall();
	if (!success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not exit wall"));
		return false;
	}
	else
	{
		return true;
	}
}
#pragma endregion

bool UFShadowAbility1::SwitchWalls(int WallID)
{
	TArray<AUShadowWall*> Walls = AliveWalls.Array();
	AUShadowWall* ChosenWall = Walls[WallID];
	if (ChosenWall->IsAlive())
	{
		//Move our current Actor
		RestrictedActor->SetActorLocationAndRotation(ChosenWall->GetActorLocation(), ChosenWall->GetActorRotation());
		RestrictedActor->AddActorLocalRotation(FRotator(90, -90, 0));
		FVector cameraDeepness = FVector(5, 10, 0);
		RestrictedActor->AddActorLocalOffset(cameraDeepness);

		CurrentWall->bISPlayerInside = false;
		ChosenWall->bISPlayerInside = true;
		CurrentWall = ChosenWall;

		return true;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Unable to enter wall"));
		return false;
	}
}


bool UFShadowAbility1::InitAbility(FVector Position)
{
	//Place a portal and grab the portal wall
	AliveWalls.Empty();

	//Grab all walls in a radius
	TSet<AUShadowWall*> Walls = DiscCastWalls(OriginalActor->GetActorLocation());

	//Add all chosen walls to AliveWalls
	AliveWalls = ChooseWalls(Walls);

	//If no walls are in range, ability should not activate
	if (AliveWalls.Num() == 0)
	{
		return false;
	}

	//Turn on every wall chosen
	TurnOnWalls();
	return true;
}

// Called every frame
void UFShadowAbility1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AbilityTickResponse(DeltaTime);

	if (ShadowState == EAbilityState::Cue && OriginalActor)
	{
		CueWallVisible(DeltaTime);
	}
}

