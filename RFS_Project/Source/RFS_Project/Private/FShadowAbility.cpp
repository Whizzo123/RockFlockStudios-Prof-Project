// Fill out your copyright notice in the Description page of Project Settings.


#include "FShadowAbility.h"

// Sets default values for this component's properties
UFShadowAbility::UFShadowAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bActivated = false;
	bExitedPortal = false;
	bEnteredPortal = false;
	bPortalUseable = false;
	bGreenMaterial = false;
	bInitiated = false;
	// ...
}


// Called when the game starts
void UFShadowAbility::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Starting Shadow Ability"));
	// ...

}

FVector UFShadowAbility::GetOriginalActorForwardVector() {
	if (!OriginalActor)
		return FVector(0, 0, 1);

	FVector fwdVec;
	UCameraComponent* CameraComps = Cast<UCameraComponent>(OriginalActor->GetComponentByClass(UCameraComponent::StaticClass()));
	if (CameraComps)
		return CameraComps->GetForwardVector();
	else
		return OriginalActor->GetActorForwardVector();

}
void UFShadowAbility::UseAbility()
{

	if (bExitedPortal || !OriginalActor)
		return;
	
	if (!bInitiated)
	{
		FVector location = OriginalActor->GetActorLocation();
		FVector fwdVec = GetOriginalActorForwardVector();

		FVector portalTranslation = FVector(0, 0, 15);
		AShadowPortal* portal;
		if (PortalBP)
			portal = GetWorld()->SpawnActor<AShadowPortal>(PortalBP, OriginalActor->GetActorLocation(), FRotator(0));
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::PlacePortal : ShadowPortalBP has not been assigned"));
			return;
		}
		//Pass in boolean to allow portal to let player inside and translate it so it is infront of the wall
		portal->AddActorLocalOffset(portalTranslation);
		Portal = portal;
		bInitiated = true;

		return;
	}
	if (!bActivated)
	{
		DestroyOrHideActor(Portal);
		Portal = nullptr;
		if (UseAmount <= 0) {

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Out of Ability Uses"));
			return;
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Using Ability"));
		FVector location = OriginalActor->GetActorLocation();
		FVector fwdVec = GetOriginalActorForwardVector();
		bool success = InitAbility(location, fwdVec);
		if (!success)
		{
			bInitiated = false;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Initialising ability failed"));
			return;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Ability activated"));
			DurationTimer = Duration;
			bActivated = true;
			UseAmount--;
			DepleteCharge();
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
	Portal->Init(&bPortalUseable);

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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: Walls activated %i"), i));

	return true;
}
void UFShadowAbility::UpdateFakeWall(FVector position, FVector fwdVector) {
	FVector endPosition = position + (fwdVector * Range);
	FCollisionQueryParams traceParams;

	TArray<FHitResult> hits;
	bool wallFound = false;
	FVector savedPoint = endPosition;//If we never find any hits, just set it to the end of the array
	FRotator savedRotation = FRotator(0);//If we never find any hits, just set it to the end of the array
	GetWorld()->LineTraceMultiByChannel(hits, position, endPosition, ECC_Visibility, traceParams);
	for (int i = 0; i < hits.Num(); i++)
	{

		AUShadowWall* wall = Cast<AUShadowWall>(hits[i].GetActor());
		if (i >= 4)
			break;//We will break out with a false wallFound
		if (wall)
		{
			FVector hitsNormal = hits[i].Normal;
			FVector wallNormal = hits[i].GetActor()->GetActorUpVector();
			if (hitsNormal.Equals(wallNormal))
			{
				savedPoint = hits[i].Location;
				savedRotation = hits[i].GetActor()->GetActorRotation();
				wallFound = true;

				
				break;
			}

		}
	}



	if (!wallFound)
	{
		for (int i = 0; i < hits.Num(); i++)
		{
			if (!Cast<AShadowPortal>(hits[i].GetActor())) {
				savedPoint = hits[i].Location;//If we don't find a valid wall, put it on the first hit
				//Get the surface normal and rotate based on that
				//Source:https://forums.unrealengine.com/t/rotation-from-normal/11543/3 used the two posts from TS100101 and janousch
				FVector hitsNormal = hits[i].Normal;
				FQuat RootQuat = Portal->GetActorQuat();
				FVector UpVector = RootQuat.GetUpVector();
				FVector RotationAxis = FVector::CrossProduct(UpVector, hitsNormal);
				RotationAxis.Normalize();

				float DotProduct = FVector::DotProduct(UpVector, hitsNormal);
				float RotationAngle = acosf(DotProduct);

				FQuat Quat = FQuat(RotationAxis, RotationAngle);

				FQuat NewQuat = Quat * RootQuat;
				Portal->SetActorRotation(NewQuat.Rotator());
				break;
			}
		}

	}

	if (GreenMaterial && RedMaterial)
	{
		if (wallFound) {
			if (!bGreenMaterial)
			{
				bGreenMaterial = true;
				Portal->PortalPlane->SetMaterial(0, GreenMaterial);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Green Material"));
			}
		}
		else {
			if (bGreenMaterial)
			{
				bGreenMaterial = false;
				Portal->PortalPlane->SetMaterial(0, RedMaterial);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Red Material"));
			}
		}
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Valid and Invalid materials have not been set"));


	Portal->SetActorLocation(savedPoint);
	FVector portalTranslation = FVector(0, 0, 15);
	Portal->AddActorLocalOffset(portalTranslation);
	if (savedRotation != FRotator(0))
		Portal->SetActorRotation(savedRotation);
}
bool UFShadowAbility::PlacePortal(FVector position, FVector fwdVector)
{

		FVector endPosition = position + (fwdVector * Range);
		FCollisionQueryParams traceParams;
		FVector portalTranslation = FVector(0, 0, 15);

		////Spawn Portal
		//FHitResult hit;
		//GetWorld()->LineTraceSingleByChannel(hit,position, endPosition, ECC_Visibility, traceParams);
		//AUShadowWall* wall = Cast<AUShadowWall>(hit.GetActor());
		//if (wall)
		//{
		//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("I have hit a SolidWall"));
		//	FActorSpawnParameters SpawnParams;
		//	AShadowPortal* portal;
		//	if (PortalBP)
		//		portal = GetWorld()->SpawnActor<AShadowPortal>(PortalBP, hit.Location, hit.GetActor()->GetActorRotation());
		//	else {
		//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::PlacePortal : ShadowPortalBP has not been assigned"));
		//		return false;
		//	}
		//	//Pass in boolean to allow portal to let player inside and translate it so it is infront of the wall
		//	portal->AddActorLocalOffset(portalTranslation);
		//	portal->Init(&bPortalUseable);
		//	PortalWall = wall;
		//	Portal = portal;
		//	
		//}
		//else {
		//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I have NOT hit a SolidWall"));
		//	return false;
		//}
		// 

		//My problem with this implementation is that, if we trace through walls and hit a shadow wall through layers of visible walls, we won't know where our shadow wall has ended up in.
		TArray<FHitResult> hits;
		FHitResult hit;
		AUShadowWall* wall= nullptr;
		bool wallFound = false;
		GetWorld()->LineTraceMultiByChannel(hits, position, endPosition, ECC_Visibility, traceParams);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("hits amount: %i"), hits.Num()));
		for (int i = 0; i < hits.Num(); i++)
		{
			wall = Cast<AUShadowWall>(hits[i].GetActor());
			if (i >= 2)
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
		//GetWorld()->LineTraceSingleByChannel(hit, savedLineLocation, (down*Range) + savedLineLocation, ECC_Visibility, traceParams);
		GetWorld()->LineTraceMultiByChannel(hits, savedLineLocation, (down * Range) + savedLineLocation, ECC_Visibility, traceParams);
		

		float halfHeight = 100;
		FVector off = FVector(0, 0, (hits[hits.Num() -1].Distance * -1) + halfHeight);
		Portal->AddActorWorldOffset(off);
		return true;

}

TSet<AUShadowWall*> UFShadowAbility::SphereCastWalls(FVector origin)
{
	TSet<AUShadowWall*> shadowWalls;
	FCollisionQueryParams traceParams;
	TArray<FHitResult> hits;
	GetWorld()->SweepMultiByChannel(hits, origin, origin, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(SphereRange), traceParams);

	//Goes through all objects hit adn grabs the walls and adds them to TSet
	for (int i = 0; i < hits.Num(); i++)
	{
		AUShadowWall* wall = Cast<AUShadowWall>(hits[i].GetActor());
		if (wall) {
			shadowWalls.Add(wall);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility::SphereCastWalls: Walls found %i"), shadowWalls.Num()));
	return shadowWalls;

	//My problem with this function is that it could be a lot less performant than a sphere cast, however it would restrict it to our level
	/*TArray<FHitResult> hits;
	int radialAccuracy = 10;
	for (int i = 1; i < radialAccuracy; i++)
	{
		float yawAmount = ((360 / radialAccuracy) * i);
		FVector endVector(1, 0, 0);
		endVector.RotateAngleAxis(yawAmount, FVector3d(0, 0, 1));
		endVector *= SphereRange;
		GetWorld()->LineTraceMultiByChannel(hits, origin, origin + endVector, ECC_Visibility);

		for (int actors = 0; actors < hits.Num(); actors++)
		{
			AUShadowWall* wall = Cast<AUShadowWall>(hits[actors].GetActor());
			if (wall) {
				shadowWalls.Add(wall);
			}
		}
	}
	return shadowWalls;*/

}

TSet<AUShadowWall*> UFShadowAbility::ChooseWalls(TSet<AUShadowWall*> walls)
{
	TArray<AUShadowWall*> aWalls = walls.Array();
	TSet<AUShadowWall*> newWalls = TSet<AUShadowWall*>();
	int wallCount = 1;//Starting at 1 to account for the initial wall hit
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
	FVector cameraDeepness = FVector(5, 10, 0);
	restrictedCharacter->AddActorLocalOffset(cameraDeepness);
	RestrictedActor = restrictedCharacter;

	//Repossess original actor
	//TODO: Animation should play to make the original character go into the wall
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);
	OriginalActor->SetActorLocationAndRotation(restrictedCharacter->GetActorLocation(), restrictedCharacter->GetActorRotation());
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 500));
	con->Possess(RestrictedActor);
	DestroyOrHideActor(Portal);
	Portal = nullptr;

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
	OriginalActor->SetActorLocationAndRotation(RestrictedActor->GetActorLocation(), RestrictedActor->GetActorRotation());
	OriginalActor->AddActorWorldOffset(OriginalActor->GetActorForwardVector() * 300);//shoudl play animation for exiting
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 20));
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);
	DestroyOrHideActor(RestrictedActor);
	RestrictedActor = nullptr;
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
		DestroyOrHideActor(Portal);
		Portal = nullptr;
	}
	for (auto& Elem : AliveWalls)
	{
		//Elem->ResetWall();
		Elem->OnDeath();
	}
	bInitiated = false;
	bActivated = false;
	bExitedPortal = false;
	bEnteredPortal = false;
	bPortalUseable = false;
	bGreenMaterial = false;
	DurationTimer = Duration;
}
void UFShadowAbility::DestroyOrHideActor(AActor* actor)
{
	if (actor)
	{
		bool destroyed = actor->Destroy();
		if (!destroyed)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::DestroyOrHideActor : Couldn't destroy actor, attempting to hide"));
		else {
			actor->AddActorWorldOffset(FVector(0, 500, 0));
			actor->SetActorHiddenInGame(true);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::DestroyOrHideActor : Actor does not exist?"));

	}
}

// Called every frame
void UFShadowAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bInitiated && !bActivated && OriginalActor && Portal)
		UpdateFakeWall(OriginalActor->GetActorLocation(), GetOriginalActorForwardVector());
	if (!bActivated)
		return;
	DurationTimer -= DeltaTime;
	GEngine->AddOnScreenDebugMessage(-2, 15.0f, FColor::Black, FString::Printf(TEXT("FShadowAbility Duration: %f"), DurationTimer, false));

	if (DurationTimer < 0 || !PortalWall->alive)
		EndAbility();

}

