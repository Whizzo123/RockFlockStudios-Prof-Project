// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility.h"

// Sets default values for this component's properties
UFShadowAbility::UFShadowAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bPortalUseable = false;
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
	FVector fwdVec = GetCameraActorForwardVector(OriginalActor);
	FVector location = OriginalActor->GetActorLocation() + (fwdVec * 100);
	bool success = InitAbility(location, fwdVec);
	if (!success)
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
	if (!bPortalUseable) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Portal is not in range"));
		return false;
	}
	bool success = EnterWall(PortalWall);
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
		BPI_ActiveState();
		return true;
	}
}
bool UFShadowAbility::EnteredState() {
	bool success = ExitWall();
	if (!success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not exit portal"));
		return false;
	}
	else 
	{
		BPI_ExitWall();
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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: Current State %i was %i"), int(ShadowState), bSuccess));
			break;
		}
		case EAbilityState::Cue:
		{
			bSuccess = CueState();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: Current State %i was %i"), int(ShadowState), bSuccess));
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
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: Current State %i was %i"), int(ShadowState), bSuccess));
			}
			else
			{
				bSuccess = EnteredState();
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: Current State %i + 1(In Portal) was %i"), int(ShadowState), bSuccess));
				if (bSuccess)
				{
					ShadowState = EAbilityState::Inactive;
					EndAbility();
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
	Portal->Init(&bPortalUseable);

	//Grab all walls in a radius
	TSet<AUShadowWall*> Walls = DiscCastWalls(Portal->GetActorLocation());
	Walls.Remove(PortalWall);

	//Add all chosen walls to AliveWalls
	AliveWalls = ChooseWalls(Walls);
	AliveWalls.Add(PortalWall);
	

	//Turn on every wall chosen
	int VFXId = 0;
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->StartWall(VFXId);//We have passed in the iterator for VFX
		VFXId++;
	}
	return true;
}
bool UFShadowAbility::PlacePortal(FVector position, FVector fwdVector)
{

		FVector endPosition = position + (fwdVector * Range);
		FCollisionQueryParams traceParams;
		FVector portalTranslation = FVector(0, 0, 15);

		//My problem with this implementation is that, if we trace through walls and hit a shadow wall through layers of visible walls, we won't know where our shadow wall has ended up in.
		TArray<FHitResult> hits;
		FHitResult hit;
		AUShadowWall* wall= nullptr;
		bool wallFound = false;
		GetWorld()->LineTraceMultiByChannel(hits, position, endPosition, ECC_Visibility, traceParams);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("hits amount: %i"), hits.Num()));
		for (int i = 0; i < hits.Num(); i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, hits[i].GetActor()->GetName());
			wall = Cast<AUShadowWall>(hits[i].GetActor());
			if (i >= 4)
				return false;//We will return false to prevent our trace going through physical walls, If we have hit two walls, assume we have went through too many
			if (wall)
			{
				FVector hitsNormal = hits[i].Normal;
				int32 hitsInbetween = i;//If there were 4 hits, we may assume that this coming wall hit is behind other walls and should not be executed.			
				FVector wallNormal = hits[i].GetActor()->GetActorUpVector();
				if (hitsNormal.Equals(wallNormal))
				{
					FActorSpawnParameters SpawnParams;
					AShadowPortal* portal;
					if (PortalBP)
						portal = GetWorld()->SpawnActor<AShadowPortal>(PortalBP, hits[i].Location, hits[i].GetActor()->GetActorRotation());
					else {
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::PlacePortal : ShadowPortalBP has not been assigned"));
						return false;
					}
					//Pass in boolean to allow portal to let player inside and translate it so it is infront of the wall
					portal->AddActorLocalOffset(portalTranslation);
					PortalWall = wall;
					Portal = portal;
					wallFound = true;
					hit = hits[i];
					break;
		
				}

			}
		}
		if (!wallFound || wall == nullptr)
			return false;
		

		//TODO: Remove
		//Reposition portal with correct vertical offset
		FVector savedLineLocation = hit.Location;
		FVector down = FVector(0, 0, -1);
		traceParams.AddIgnoredActor(wall);
		GetWorld()->LineTraceMultiByChannel(hits, savedLineLocation, (down * Range) + savedLineLocation, ECC_Visibility, traceParams);
		

		float halfHeight = 100;
		FVector off = FVector(0, 0, (hits[hits.Num() -1].Distance * -1) + halfHeight);
		Portal->AddActorWorldOffset(off);
		return true;

}



void UFShadowAbility::EndAbility()
{
	//Exit's wall if we are in it, destroys portal if it's active
	if (ShadowState == EAbilityState::Active){
		if (bInsideWalls)
			ExitWall();
		DestroyOrHideActor(Portal);
		Portal = nullptr;
	}

	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->OnDeath();
	}
	//Reset parameters
	ShadowState = EAbilityState::Inactive;
	bPortalUseable = false;
	bInsideWalls = false;
	DurationTimer = Duration;
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

	if (ShadowState == EAbilityState::Active || bInsideWalls)
	{
		DurationTimer -= DeltaTime;
		GEngine->AddOnScreenDebugMessage(-2, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility Duration: %f"), DurationTimer, false));

		//If our wall get's destroyed or we run out of time. End the ability
		if (DurationTimer < 0 || !PortalWall->alive)
		{
			EndAbility();
		}
	}
}

void UFShadowAbility::UpdateFakePortal(FVector Position, FVector FwdVector) {
	/*Will continually line trace for a valid object to hit.
	If the object is a AUShadowWall, the portal will turn green.
	If the object is anything else, the portal will turn red.
	*/
	bool bWallFound = false;
	bool bFake = false;
	FVector EndPosition = Position + (FwdVector * Range);
	FVector SavedPoint = EndPosition;//If we never find any hits, just set it to the end of the array
	FRotator SavedRotation = FRotator(0);//If we never find any hits, just set it to the end of the array
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
			if (!Cast<AShadowPortal>(Hits[i].GetActor()) && !bFake) {
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
	Portal->SetActorRotation(SavedRotation);
}
