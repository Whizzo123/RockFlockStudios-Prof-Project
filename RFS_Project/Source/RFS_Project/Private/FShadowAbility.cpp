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
	/*bool debug = true;
	if (!debug)
	{
		if (UseAmount <= 0)
			return;

		UseAmount--;
	}
	if (UseAmount <= 0)
		return;

	UseAmount--;*/
	if (bExitedPortal)
		return;

	if (!bActivated)
	{
		FVector location = OriginalActor->GetActorLocation();
		FVector fwdVec = OriginalActor->GetActorForwardVector();
		bool success = InitAbility(location, fwdVec);
		if (!success)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));
			return;
		}
		else {
			DurationTimer = Duration;
			bActivated = true;
			return;
		}
	}
	else {
		if (!bEnteredPortal)
		{
			if (!bPortalUseable) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Portal is not in range"));   
				return;
			}
			EnterPortal();
			DurationTimer = Duration * DurationMultiplier;
			bEnteredPortal = true;
			return;

		}
		else {
			ExitWall();
			DurationTimer = DurationEndStart;
			bExitedPortal = true;
			return;
		}
	}
	//Use Ability
	//PlacePortal(OriginalActor->GetActorLocation(), OriginalActor->GetActorForwardVector());
}

void UFShadowAbility::Init(APawn* actor)
{
	OriginalActor = actor;
}

bool UFShadowAbility::InitAbility(FVector position, FVector fwdVector)
{
	AliveWalls.Empty();
	bool success = PlacePortal(position, fwdVector);

	if (!success)
		return false;

	TSet<AUShadowWall*> walls = SphereCastWalls(position);

	walls.Remove(PortalWall);

	AliveWalls = EnableWalls(walls);
	AliveWalls.Add(PortalWall);
	return true;
}

bool UFShadowAbility::PlacePortal(FVector position, FVector fwdVector)
{

		FVector endPosition = (fwdVector * Range) + position;
		FCollisionQueryParams traceParams;
		FHitResult hit;
		FVector portalTranslation = FVector(0, 0, 15);

		//Spawn Portal
		GetWorld()->LineTraceSingleByChannel(hit,position,fwdVector, ECC_Visibility, traceParams);
		AUShadowWall* wall = Cast<AUShadowWall>(hit.GetActor());
		if (wall)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have hit a SolidWall"));
			//Spawn Portal with correct horizontal offset and rotation
			AShadowPortal* portal = GetWorld()->SpawnActor<AShadowPortal>(hit.Location, hit.GetActor()->GetActorRotation());
			portal->AddActorLocalOffset(portalTranslation);
			PortalWall = wall;
			Portal = portal;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have NOT hit a SolidWall"));
			return false;
		}

		//Reposition portal with correct vertical offset
		FVector savedLineLocation = hit.Location;
		FVector down = FVector(0, 0, -1);
		traceParams.AddIgnoredActor(wall);
		GetWorld()->LineTraceSingleByChannel(hit, savedLineLocation, (down*Range) + savedLineLocation, ECC_Visibility, traceParams);

		float halfHeight = 100;
		FVector off = FVector(0, 0, (hit.Distance * -1) + halfHeight);
		Portal->AddActorWorldOffset(off);

		PortalWall->StartWall();
		return true;

}

TSet<AUShadowWall*> UFShadowAbility::SphereCastWalls(FVector origin)
{
	TSet<AUShadowWall*> shadowWalls;
	FCollisionQueryParams traceParams;
	TArray<FHitResult> hits;
	GetWorld()->SweepMultiByChannel(hits, origin, origin, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(SphereRange), traceParams);

	for (int i = 0; i < hits.Num(); i++)
	{
		AUShadowWall* wall = Cast<AUShadowWall>(hits[i].GetActor());
		if (wall) {
			shadowWalls.Add(wall);
		}
	}
	return shadowWalls;

}

TSet<AUShadowWall*> UFShadowAbility::EnableWalls(TSet<AUShadowWall*> walls)
{
	TSet<AUShadowWall*> newWalls;
	FQuat OriginalRotation;
	FVector Bounds;
	int wallCount = 1;
	if (walls.Num() == 0)
		return newWalls;

	TArray<AUShadowWall*> aWalls = walls.Array();
	for (int i = 2; i < WallAmount; i++)
	{
		int index = FMath::RandRange(0, walls.Num());
		newWalls.Add(aWalls[index]);
		aWalls.RemoveAt(index);
		wallCount++;
	}
	FString text = "Walls Actived:" + wallCount;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
	return newWalls;

}

void UFShadowAbility::EnterPortal()
{
	Cast<IIShadowPawn>(OriginalActor)->ToggleCollisionPhysics();
	AARestrictedCamera* restrictedCharacter = GetWorld()->SpawnActor<AARestrictedCamera>(Portal->GetActorLocation(), Portal->GetActorRotation());
	restrictedCharacter->AddActorLocalRotation(FRotator(0,90,-90));
	restrictedCharacter->AddActorLocalOffset(FVector( - 50, 10, 0));
	RestrictedActor = restrictedCharacter;

	//TODO: Animation should play to make the original character go into the wall
	OriginalActor->SetActorLocationAndRotation(restrictedCharacter->GetActorLocation(), restrictedCharacter->GetActorRotation());
	GetOwner()->GetInstigatorController()->Possess(RestrictedActor);
	Portal->Destroy();
}

void UFShadowAbility::ExitWall()
{
	GetOwner()->GetInstigatorController()->Possess(OriginalActor);
	RestrictedActor->Destroy();

	OriginalActor->AddActorLocalOffset(OriginalActor->GetActorForwardVector() * 200);
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 50));
	Cast<IIShadowPawn>(OriginalActor)->ToggleCollisionPhysics();

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
	for (auto& Elem : AliveWalls)
	{
		Elem->ResetWall();
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

