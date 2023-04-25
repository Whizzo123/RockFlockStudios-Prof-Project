// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility.h"

// Sets default values for this component's properties
UFShadowAbility::UFShadowAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWithinPortalRange = false;
	ShadowState = EAbilityState::Inactive;
	// ...
}


// Called when the game starts
void UFShadowAbility::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Starting Shadow Ability"));
	// ...

}


#pragma region STATE_FUNCTIONS
bool UFShadowAbility::InactiveState() {
	//Spawns a fake wall which gets updated in tick
	//Do we have uses
	if (UseData.Use <= 0) 
	{

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Out of Ability Uses"));
		return false;
	}

	//Spawn a portal but do not call Init
	AShadowPortal* FakePortal;
	if (PortalBP)
	{
		FakePortal = GetWorld()->SpawnActor<AShadowPortal>(PortalBP, OriginalActor->GetActorLocation(), FRotator(0));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::PlacePortal : ShadowPortalBP has not been assigned"));
		return false;
	}

	FakePortal->AddActorLocalOffset(FVector(0, 0, 15));//Translation to make the portal appear in front of the wall
	Portal = FakePortal;
	BPI_InactiveState();
	return true;
}
bool UFShadowAbility::CueState() {
	//Destroy the InactiveState's portal
	DestroyOrHideActor(Portal);
	Portal = nullptr;

	//Place the portal and activate the walls
	FVector FwdVec = GetCameraActorForwardVector(OriginalActor);
	FVector Location = OriginalActor->GetActorLocation() + (FwdVec * 100);
	bool bSuccess = InitAbility(Location, FwdVec);
	if (!bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));
		return false;
	}
	else 
	{
		DurationTimer = Duration;
		UseData.Use--;
		DepleteCharge();
		BPI_CueState();
		return true;
	}
}
bool UFShadowAbility::ActiveState() {
	//Are we in portal range
	if (!bWithinPortalRange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Portal is not in range"));
		return false;
	}
	bool success = EnterWall(CurrentWall);
	if (!success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not enter portal"));
		return false;
	}
	else 
	{
		DestroyOrHideActor(Portal);
		Portal = nullptr;
		DurationTimer = DurationTimer * DurationMultiplier;
		bInsideWalls = true;
		BPI_ActiveState();
		return true;
	}
}
bool UFShadowAbility::EnteredState() {
	bool success = ExitWall();
	if (!success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not exit wall"));
		return false;
	}
	else 
	{
		bInsideWalls = false;
		DurationTimer = DurationEndStart;
		return true;
	}
}
#pragma endregion

bool UFShadowAbility::Use()
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
			if (!bSuccess)
			{
				ShadowState = EAbilityState::Inactive;
			}
			break;
		}
		case EAbilityState::Active:
		{
			//There are two things we can do in Active, enter the portal and exit the portal. 
			//When we exit, we will go back to the inactive state
			if (!bInsideWalls)
			{
				bSuccess = ActiveState();
			}
			else
			{
				bSuccess = EnteredState();
				if (bSuccess)
				{
					ShadowState = EAbilityState::Inactive;
				}
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


bool UFShadowAbility::InitAbility(FVector position, FVector fwdVector)
{
	//Place a portal and grab the portal wall
	AliveWalls.Empty();
	bool bSuccess = PlacePortal(position, fwdVector);
	if (!bSuccess)
	{
		return false;
	}
	Portal->Init(&bWithinPortalRange);

	//Grab all walls in a radius
	TSet<AUShadowWall*> Walls = DiscCastWalls(Portal->GetActorLocation());
	Walls.Remove(CurrentWall);

	//Add all chosen walls to AliveWalls
	AliveWalls = ChooseWalls(Walls);
	AliveWalls.Add(CurrentWall);
	
	
	//Turn on every wall chosen
	TurnOnWalls();
	return true;
}
bool UFShadowAbility::PlacePortal(FVector Position, FVector FwdVector)
{
	//WARNING: When changing this function, change UpdateFakePortal
		FVector EndPosition = Position + (FwdVector * Range);
		FVector PortalTranslation = FVector(0, 0, 15);

		//My problem with this implementation is that, if we trace through walls and hit a shadow wall through layers of visible walls, we won't know where our shadow wall has ended up in.
		TArray<FHitResult> Hits;
		FHitResult Hit;
		AUShadowWall* Wall= nullptr;
		bool WallFound = false;
		GetWorld()->LineTraceMultiByChannel(Hits, Position, EndPosition, ECC_Visibility);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("hits amount: %i"), Hits.Num()));
		for (int i = 0; i < Hits.Num(); i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, Hits[i].GetActor()->GetName());
			Wall = Cast<AUShadowWall>(Hits[i].GetActor());
			if (i >= 6)
			{
				return false;//We will return false to prevent our trace going through physical walls, If we have hit two walls, assume we have went through too many
			}
			if (Wall)
			{
				FVector HitsNormal = Hits[i].Normal;
				int32 HitsInbetween = i;//If there were 4 hits, we may assume that this coming wall hit is behind other walls and should not be executed.			
				FVector WallNormal = Hits[i].GetActor()->GetActorUpVector();
				if (HitsNormal.Equals(WallNormal))
				{
					FActorSpawnParameters SpawnParams;
					AShadowPortal* NewPortal;
					if (PortalBP)
					{
						NewPortal = GetWorld()->SpawnActor<AShadowPortal>(PortalBP, Hits[i].Location, Hits[i].GetActor()->GetActorRotation());
					}
					else 
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::PlacePortal : ShadowPortalBP has not been assigned"));
						return false;
					}
					//Pass in boolean to allow portal to let player inside and translate it so it is infront of the wall
					NewPortal->AddActorLocalOffset(PortalTranslation);
					CurrentWall = Wall;
					Portal = NewPortal;
					WallFound = true;
					Hit = Hits[i];
					break;
		
				}

			}
		}
		if (!WallFound || Wall == nullptr)
			return false;
		

		//TODO: Remove?
		//Reposition portal with correct vertical offset
		FVector SavedLineLocation = Hit.Location;
		FVector Down = FVector(0, 0, -1);
		FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
		TraceParams.AddIgnoredActor(Wall);
		GetWorld()->LineTraceMultiByChannel(Hits, SavedLineLocation, (Down * Range) + SavedLineLocation, ECC_Visibility, TraceParams);
		

		float HalfHeight = 100;
		FVector Off = FVector(0, 0, (Hits[Hits.Num() -1].Distance * -1) + HalfHeight);
		Portal->AddActorWorldOffset(Off);
		return true;

}


void UFShadowAbility::EndAbility()
{
	//Exit's wall if we are in it, destroys portal if it's active
	if (ShadowState == EAbilityState::Active){
		if (bInsideWalls)
		{
			ExitWall();
		}
		if (Portal)
		{
			Portal->PortalDeath();
			Portal = nullptr;
		}

	}

	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->OnDeath();
	}
	//Reset parameters
	ShadowState = EAbilityState::Inactive;
	bWithinPortalRange = false;
	bInsideWalls = false;
	DurationTimer = -1;
	BPI_EndAbility();

}

// Called every frame
void UFShadowAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShadowState == EAbilityState::Cue && OriginalActor && Portal)
	{
		UpdateFakePortal(OriginalActor->GetActorLocation(), GetCameraActorForwardVector(OriginalActor));
	}
	AbilityTickResponse(DeltaTime);


}

void UFShadowAbility::UpdateFakePortal(FVector Position, FVector FwdVector) {
	/*Will continually line trace for a valid object to hit.
	If the object is a AUShadowWall, the portal will turn green.
	If the object is anything else, the portal will turn red.
	*/
	//WARNING: When changing this function, change PlacePortal

	bool bWallFound = false;
	bool bFake = false;
	FVector EndPosition = Position + (FwdVector * Range);
	FVector SavedPoint = EndPosition;//If we never find any hits, just set it to the end of the array
	FRotator SavedRotation = FRotator(0) ;//If we never find any hits, just set it to the end of the array
	TArray<FHitResult> Hits;
	GetWorld()->LineTraceMultiByChannel(Hits, Position, EndPosition, ECC_Visibility);
	for (int i = 0; i < Hits.Num(); i++)
	{

		AUShadowWall* wall = Cast<AUShadowWall>(Hits[i].GetActor());
		//We cannot grab a wall if we have linetraced through this many actors
		if (i >= 6)
			break;//We will break out with a false wallFound
		if (wall)
		{
			//The wall has to be facing us to be considered
			FVector HitsNormal = Hits[i].Normal;
			FVector WallNormal = Hits[i].GetActor()->GetActorUpVector();
			if (HitsNormal.Equals(WallNormal))
			{
				//We have found a wall
				SavedPoint = Hits[i].Location;
				SavedRotation = Hits[i].GetActor()->GetActorRotation();
				bWallFound = true;
				break;
			}

		}
		else {
			//We can't place the portal on itself
			if (!Cast<AShadowPortal>(Hits[i].GetActor()) && !bFake && Hits[i].GetActor() != OriginalActor) {
				FString string = Hits[i].GetActor()->GetFName().GetPlainNameString();
				GEngine->AddOnScreenDebugMessage(5, 15.0f, FColor::Green, string);
				bFake = true;
				//If we don't find a valid wall, put it on the first hit
				SavedPoint = Hits[i].Location;
				//Get the surface normal and rotate based on that
				//Source:https://forums.unrealengine.com/t/rotation-from-normal/11543/3 used the two posts from TS100101 and janousch
				FVector hitsNormal = Hits[i].Normal;
				FQuat RootQuat = Portal->GetActorQuat();
				FVector UpVector = RootQuat.GetUpVector();
				FVector RotationAxis = FVector::CrossProduct(UpVector, hitsNormal);
				RotationAxis.Normalize();

				float DotProduct = FVector::DotProduct(UpVector, hitsNormal);
				float RotationAngle = acosf(DotProduct);

				FQuat Quat = FQuat(RotationAxis, RotationAngle);

				FQuat NewQuat = Quat * RootQuat;
				Portal->SetActorRotation(NewQuat.Rotator());
			}
		}
	}


	//Change the material
	if (GreenMaterial && RedMaterial)
	{
		if (bWallFound) 
		{
			if (Portal->PortalPlane->GetMaterial(0) != GreenMaterial)
			{
				
				Portal->PortalPlane->SetMaterial(0, GreenMaterial);
			}
		}
		else 
		{
			if (Portal->PortalPlane->GetMaterial(0) != RedMaterial)
			{
				Portal->PortalPlane->SetMaterial(0, RedMaterial);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Valid and Invalid materials have not been set"));
	}

	//Set location and rotation
	Portal->SetActorLocation(SavedPoint);
	Portal->AddActorLocalOffset(FVector(0, 0, 15));//Translation to make the portal appear in front of the wall
	if (SavedRotation != FRotator(0))
	{
		Portal->SetActorRotation(SavedRotation);
	}
}
