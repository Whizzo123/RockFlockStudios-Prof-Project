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
bool UFShadowAbility1::SwitchWalls(int WallID)
{
	TArray<AUShadowWall*> Walls = AliveWalls.Array();
	AUShadowWall* ChosenWall = Walls[WallID];
	if (ChosenWall->alive)
	{
		//Move our current Actor
		RestrictedActor->SetActorLocationAndRotation(ChosenWall->GetActorLocation(), ChosenWall->GetActorRotation());
		RestrictedActor->AddActorLocalRotation(FRotator(90, -90, 0));
		FVector cameraDeepness = FVector(5, 10, 0);
		RestrictedActor->AddActorLocalOffset(cameraDeepness);
		
		CurrentWall = ChosenWall;
		return true;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Unable to enter wall"));
		return false;
	}
}
bool UFShadowAbility1::InactiveState() {
	//Do we have uses
	if (UseData.Use <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Out of Ability Uses"));
		return false;
	}

	
	BPI_InactiveState();//Should Play animation for cueing the ability
	return true;
}
bool UFShadowAbility1::CueState() {

	//Place the portal and activate the walls
	FVector Location = OriginalActor->GetActorLocation();
	bool bSuccess = InitAbility(Location);
	if (!bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));
		return false;
	}
	else
	{
		CurrentWall = AliveWalls.Array()[0];
		bSuccess = EnterWall(CurrentWall);
		if (!bSuccess)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Couldn't enter wall"));
			return false;
		}
		//Start ability data
		DurationTimer = Duration;
		bInsideWalls = true;
		UseData.Use--;
		DepleteCharge();
		
		BPI_CueState();//We should be teleported inside the walls
		return true;
	}
}
bool UFShadowAbility1::ActiveState() {
	//Are we in portal range
	bool success = ExitWall();
	if (!success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not exit wall"));
		return false;
	}
	else
	{
		DurationTimer = DurationEndStart;
		bInsideWalls = false;
		BPI_ActiveState();
		return true;
	}
}
#pragma endregion

bool UFShadowAbility1::Use()
{

	if (!OriginalActor)
	{
		return false;
	}


	bool bSuccess = false;
	switch (ShadowState)
	{
	case EAbilityState::Inactive:
	{
		bSuccess = InactiveState();
		break;
	}
	case EAbilityState::Cue:
	{
		bSuccess = CueState();
		//When failing Cue for any reason, we will return to default state and not use ability
		if (!bSuccess)
		{
			ShadowState = EAbilityState::Inactive;
		}
		break;
	}
	case EAbilityState::Active:
	{
		//There are two things we can do in Active, switch portals or exit
		//When we exit, we will go back to the inactive state
		bSuccess = ActiveState();
		//We have successfully exited, therefor reset ability.
		if (bSuccess)
		{
			ShadowState = EAbilityState::Inactive;
		}
		return true;
	}
	default:
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility: Current State when called: Invalid State"));
		break;
	}
	}
	if (bSuccess)
	{
		ShadowState = EAbilityState(int(ShadowState) + 1);
		return true;
	}
	return false;
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
	int VFXId = 0;
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->StartWall(VFXId);//We have passed in the iterator for VFX
		VFXId++;
	}
	return true;
}


void UFShadowAbility1::EndAbility()
{
	//Exit's wall if we are in it, destroys portal if it's active
	if (ShadowState == EAbilityState::Active) {
		if (bInsideWalls)
		{
			ExitWall();
		}
	}

	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->OnDeath();
	}
	//Reset parameters
	ShadowState = EAbilityState::Inactive;
	bInsideWalls = false;
	BPI_EndAbility();

}

// Called every frame
void UFShadowAbility1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AbilityTickResponse(DeltaTime);

}

