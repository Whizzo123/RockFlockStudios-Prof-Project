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

	bActivated = false;
	bExitedPortal = false;
	bEnteredPortal = false;
	bPortalUseable = false;
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

	if (bExitedPortal)
		return;
	

	if (!bActivated)
	{
		if (UseAmount <= 0) {

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Out of Ability Uses"));
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Using Ability"));
		FVector location = OriginalActor->GetActorLocation();
		FVector fwdVec = OriginalActor->GetActorForwardVector();
		bool success = InitAbility(location, fwdVec);
		if (!success)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));
			return;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Ability activated"));
			DurationTimer = Duration;
			bActivated = true;
			UseAmount--;
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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Entering Portal"));
			bool success = EnterPortal();
			if (!success)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not enter portal"));
				return;
			}
			else {
				DurationTimer = DurationTimer * DurationMultiplier;
				bEnteredPortal = true;
				return;
			}


		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Exiting Portal"));
			bool success = ExitWall();
			if (!success)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Could not exit portal"));
				return;
			}
			else {
				DurationTimer = DurationEndStart;
				bExitedPortal = true;
				return;
			}

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
	//Place a portal and grab the portal wall
	AliveWalls.Empty();
	bool success = PlacePortal(position, fwdVector);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("FShadowAbility: Place Portal Complete"));
	if (!success)
		return false;

	//Grab all walls in a radius
	TSet<AUShadowWall*> walls = SphereCastWalls(position);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("FShadowAbility: Sphere Cast Walls Complete"));
	walls.Remove(PortalWall);

	//Add all chosen walls to AliveWalls
	AliveWalls = ChooseWalls(walls);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("FShadowAbility: Enable Walls Complete"));
	AliveWalls.Add(PortalWall);

	//Turn on every wall chosen
	int i = 0;
	for (auto& var : AliveWalls)
	{

		var->StartWall(i);
		i++;
	}
	return true;
}

bool UFShadowAbility::PlacePortal(FVector position, FVector fwdVector)
{

		FVector endPosition = position + (fwdVector * Range);
		FCollisionQueryParams traceParams;
		traceParams.bDebugQuery = true;
		FHitResult hit;
		FVector portalTranslation = FVector(0, 0, 15);

		//Spawn Portal
		GetWorld()->LineTraceSingleByChannel(hit,position, endPosition, ECC_Visibility, traceParams);
		AUShadowWall* wall = Cast<AUShadowWall>(hit.GetActor());
		if (wall)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("I have hit a SolidWall"));
			FActorSpawnParameters SpawnParams;
			AShadowPortal* portal;
			if (PortalBP)
				portal = GetWorld()->SpawnActor<AShadowPortal>(PortalBP, hit.Location, hit.GetActor()->GetActorRotation());
			else {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::PlacePortal : ShadowPortalBP has not been assigned"));
				return false;
			}
			portal->AddActorLocalOffset(portalTranslation);
			portal->Init(&bPortalUseable);
			PortalWall = wall;
			Portal = portal;
			
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have NOT hit a SolidWall"));
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility::SphereCastWalls: Walls found %i"), shadowWalls.Num()));
	return shadowWalls;

}

TSet<AUShadowWall*> UFShadowAbility::ChooseWalls(TSet<AUShadowWall*> walls)
{
	TArray<AUShadowWall*> aWalls = walls.Array();
	TSet<AUShadowWall*> newWalls = TSet<AUShadowWall*>();
	int wallCount = 1;
	if (walls.Num() == 0)
		return newWalls;

	//We start at 1 to account for the original portal wall
	for (int i = 1; i < WallAmount; i++)
	{
		int num = aWalls.Num();
		int index = FMath::RandRange(0, num - 1);
		bool valid = aWalls.IsValidIndex(index);
		//Choose a random wall
		if (valid)
		{
			newWalls.Add(aWalls[index]);
			aWalls.RemoveAt(index, 1, true);
			wallCount++;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("FShadowAbility::SphereCastWalls: Index %i , Num %i , Valid %i"), index, num, valid));

		}
	}
	return newWalls;

}

bool UFShadowAbility::EnterPortal()
{
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OriginalActor);
	if (!ShadowComponent) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterPortal : No IShadowPawn"));
		return false;
	}
	AController* con = OriginalActor->GetController();
	if (!con)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterPortal : No Controller"));
		return false;
	}

	//Spawn and assign RestrictedCharacter
	FActorSpawnParameters SpawnParams;
	AARestrictedCamera* restrictedCharacter;
	if (RestrictedActorBP)
		restrictedCharacter = GetWorld()->SpawnActor<AARestrictedCamera>(RestrictedActorBP, Portal->GetActorLocation(), Portal->GetActorRotation());
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterPortal : RestrictedActorBP has not been assigned"));
		return false;
	}
	restrictedCharacter->AddActorLocalRotation(FRotator(90,-90,0));
	restrictedCharacter->AddActorLocalOffset(FVector( - 100, 10, 0));
	RestrictedActor = restrictedCharacter;

	//TODO: Animation should play to make the original character go into the wall
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);
	OriginalActor->SetActorLocationAndRotation(restrictedCharacter->GetActorLocation(), restrictedCharacter->GetActorRotation());
	con->Possess(RestrictedActor);
	bool destroyed = Portal->Destroy();
	if (!destroyed)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterPortal : Couldn't destroy portal"));

	return true;
}

bool UFShadowAbility::ExitWall()
{

	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OriginalActor);
	if (!ShadowComponent) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterPortal : No IShadowPawn"));
		return false;
	}
	AController* con = RestrictedActor->GetController();
	if (!con)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterPortal : No Controller"));
		return false;
	}
	con->Possess(OriginalActor);
	bool destroyed = RestrictedActor->Destroy();
	if (!destroyed)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::ExitWall : Couldn't destroy actor"));

	OriginalActor->AddActorWorldOffset(OriginalActor->GetActorForwardVector() * 300);
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 50));
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);
	return true;
}
void UFShadowAbility::EndAbility()
{
	if (bEnteredPortal)
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
	if (!bActivated)
		return;
	DurationTimer -= DeltaTime;
	GEngine->AddOnScreenDebugMessage(-2, 15.0f, FColor::Black, FString::Printf(TEXT("FShadowAbility Duration: %f"), DurationTimer, false));

	if (DurationTimer < 0 || !PortalWall->alive)
		EndAbility();

}

