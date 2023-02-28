// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility.h"

// Sets default values for this component's properties
UFShadowAbility::UFShadowAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UseAmount = 1;
	UseCapacity = 1;
	ChargeAmount = 7;
	ChargeCapacity = 7;

	// ...
}


// Called when the game starts
void UFShadowAbility::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Starting Shadow Ability"));
	// ...

}

void UFShadowAbility::Use()
{
	bool debug = true;
	if (!debug)
	{
		if (UseAmount <= 0)
			return;

		UseAmount--;
	}
	if (UseAmount <= 0)
		return;

	UseAmount--;
	if (bExitedPortal)
		return;

	if (bActivated)
	{

	}
	else {
		FVector location = OriginalActor->GetActorLocation();
		FVector fwdVec = OriginalActor->GetActorForwardVector();
		bool success = InitAbility(location, fwdVec);
		if (!success)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));

		}
		else {
			DurationTimer = Duration;
			bActivated = true;
		}
	}
	//Use Ability
	GetWalls();
	SpawnPortals();
}

void UFShadowAbility::Init(APawn* actor)
{
	OriginalActor = actor;
}

bool UFShadowAbility::InitAbility(FVector position, FVector fwdVector)
{
	AliveWalls.Empty();
	PlacePortal(position, fwdVector);
}

bool UFShadowAbility::PlacePortal(FVector position, FVector fwdVector)
{

		FVector endPosition = (fwdVector * Range) + position;
		FCollisionQueryParams traceParams;
		FHitResult hit;

		GetWorld()->LineTraceSingleByChannel(hit,position,fwdVector, ECC_Visibility, traceParams);
		if (Cast<AUShadowWall>(hit.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have hit a SolidWall"));
			GetWorld()->SpawnActor(position, hit.GetActor().)

		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have NOT hit a SolidWall"));

		}
}

void UFShadowAbility::GetWalls()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Getting Walls"));
	FVector actorLocation = GetOwner()->GetActorLocation();
	FRotator actorRotation = GetOwner()->GetActorRotation();

	for (int currentLine = 0; currentLine < 69; currentLine++)
	{
		FVector actorForward = actorLocation + (actorRotation.Vector() * 69);
		TArray<FHitResult> hits;

		FCollisionQueryParams traceParams;
		GetWorld()->LineTraceMultiByChannel(hits, actorLocation, actorForward, ECC_Visibility, traceParams);

		for (int hitIndex = 0; hitIndex < hits.Num(); hitIndex++)
		{
			FHitResult result = hits[hitIndex];
			if (result.GetActor()->Tags.Contains("SolidWall"))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have hit a SolidWall"));
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have NOT hit a SolidWall"));

			}
		}

	}
}

void UFShadowAbility::SpawnPortals()
{

}

void UFShadowAbility::ExitWall()
{
}
void UFShadowAbility::EndAbility()
{
	if (!bEnteredPortal)
	{
		if (!bExitedPortal)
			ExitWall();
	}
	else {
		Portal->Destroy();
	}
	for each (AUShadowWall* var in AliveWalls)
	{
		var->ResetWall();
	}

	bActivated = false;
	bExitedPortal = false;
	bEnteredPortal = false;
	bPortalUseable = false;
	DurationTimer = Duration;
}


// Called every frame
void UFShadowAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

