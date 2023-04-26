// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShadowAbility.h"

// Sets default values for this component's properties
UBaseShadowAbility::UBaseShadowAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UBaseShadowAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseShadowAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UBaseShadowAbility::GetCameraActorForwardVector(AActor* ActorFwd) {
	if (!ActorFwd)
	{
		return FVector(0, 0, 0);
	}

	//Use Camera or character
	UCameraComponent* CameraComps = Cast<UCameraComponent>(ActorFwd->GetComponentByClass(UCameraComponent::StaticClass()));
	if (CameraComps)
	{
		return CameraComps->GetForwardVector();
	}
	else 
	{
		return ActorFwd->GetActorForwardVector();
	}

}
void UBaseShadowAbility::DestroyOrHideActor(AActor* Actor)
{
	if (Actor)
	{
		bool bDestroyed = Actor->Destroy();
		if (!bDestroyed)
		{
			Actor->AddActorWorldOffset(FVector(0, 500, 0));
			Actor->SetActorHiddenInGame(true);
		}
	}
}

bool UBaseShadowAbility::Use()
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
			bSuccess = ActiveState();
			return true;
		}
		default:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility: Invalid State"));
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

TSet<AUShadowWall*> UBaseShadowAbility::SphereCastWalls(FVector Origin, float SphereRange)
{
	TSet<AUShadowWall*> ShadowWalls;
	FCollisionQueryParams TraceParams;
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel(Hits, Origin, Origin, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(SphereRange), TraceParams);

	//Goes through all objects hit adn grabs the walls and adds them to TSet
	for (int Actors = 0; Actors < Hits.Num(); Actors++)
	{
		AUShadowWall* Wall = Cast<AUShadowWall>(Hits[Actors].GetActor());
		if (Wall && !Wall->bAlive) 
		{
			ShadowWalls.Add(Wall);
		}
	}
	return ShadowWalls;

}
TSet<AUShadowWall*> UBaseShadowAbility::DiscCastWalls(FVector Origin) {
	TArray<FHitResult> Hits;
	TSet<AUShadowWall*> ShadowWalls;

	//360 degrees of line tracing to detect and add AUShadowWalls
	for (int i = 1; i < DiscAccuracy; i++)
	{
		FVector EndVector(1, 0, 0);
		float YawAmount = ((360 / DiscAccuracy) * i);
		EndVector = EndVector.RotateAngleAxis(YawAmount, FVector3d(0, 0, 1));
		EndVector *= WallDetectionRange;
		//Note: There has been no way to continue a trace while the player body is inside it(for FShadowAbility not FShadowAbility1)
		//GetWorld()->LineTraceMultiByObjectType(Hits, Origin, Origin + EndVector, FCollisionObjectQueryParams::AllObjects, FCollisionParams);
		GetWorld()->LineTraceMultiByChannel(Hits, Origin, Origin + EndVector, ECC_Visibility);

		//Go through all actors hit and add relevant ones
		for (int Actors = 0; Actors < Hits.Num(); Actors++)
		{

			AUShadowWall* Wall = Cast<AUShadowWall>(Hits[Actors].GetActor());
			if (Wall && !Wall->bAlive)
			{
				ShadowWalls.Add(Wall);
			}
		}
	}
	return ShadowWalls;
}
TSet<AUShadowWall*> UBaseShadowAbility::ChooseWalls(TSet<AUShadowWall*> ShadowWalls)
{
	TArray<AUShadowWall*> Walls = ShadowWalls.Array();
	TSet<AUShadowWall*> NewWalls = TSet<AUShadowWall*>();
	int WallCount = 1;//Starting at 1 to account for the initial wall hit
	if (Walls.Num() == 0)
		return NewWalls;


	//We start at 1 to account for the original portal wall
	for (int i = 1; i < WallAmount; i++)
	{
		int Num = Walls.Num();
		int Index = FMath::RandRange(0, Num - 1);
		bool Valid = Walls.IsValidIndex(Index);
		//Choose a random wall
		if (Valid)
		{
			NewWalls.Add(Walls[Index]);
			Walls.RemoveAt(Index, 1, true);
			/*	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("FOUND WALLS ALIVE ID: %i"), wallCount));*/
			WallCount++;
		}
	}
	return NewWalls;

}
void UBaseShadowAbility::TurnOnWalls()
{
	int VFXId = 0;
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->StartWall(VFXId, bIsPlayerAbility, OriginalActor);//We have passed in the iterator for VFX
		VFXId++;
	}
}
void UBaseShadowAbility::CueWallVisible(float DeltaTime)
{
	CueWallFixedTimeChange -= DeltaTime;
	if (CueWallFixedTimeChange > 0)
	{
		return;
	}
	//Gets Walls in our sphere
	TSet<AUShadowWall*> WallsInSphere;
	WallsInSphere = SphereCastWalls(OriginalActor->GetActorLocation(), 4000);

	//We go through a first pass of making invalid walls invisible
	//Then go through a second pass of making new valid walls visible

	//Turn off visibilty on walls no longer inside the sphere and remove them from VisibleWalls Set
	for (AUShadowWall* Wall : VisibleWalls)
	{
		if (!WallsInSphere.Contains(Wall))
		{
			Wall->ChangeVisibility(false);
			VisibleWalls.Remove(Wall);
		}
	}
	//Turn on visibility on walls inside the sphere and add the to VisibleWalls
	for (AUShadowWall* Wall : WallsInSphere)
	{
		Wall->ChangeVisibility(true);
		VisibleWalls.Add(Wall);
	}
	
	CueWallFixedTimeChange = CueWallFixedTime;
}
void UBaseShadowAbility::TurnOffVisibleWalls()
{
	for (AUShadowWall* Wall : VisibleWalls)
	{
		Wall->ChangeVisibility(false);
	}
	VisibleWalls.Empty();
	CueWallFixedTimeChange = 0;
}
bool UBaseShadowAbility::EnterWall(AUShadowWall* WallToEnter)
{
	//Check our actor is valid
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OriginalActor);
	if (!ShadowComponent) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterWall : No IShadowPawn"));
		return false;
	}
	AController* Controller = OriginalActor->GetController();
	if (!Controller)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterWall : No Controller"));
		return false;
	}

	//Spawn and assign RestrictedCharacter
	FActorSpawnParameters SpawnParams;
	AARestrictedCamera* WallPlayerPawn;
	if (RestrictedActorBP)
	{
		WallPlayerPawn = GetWorld()->SpawnActor<AARestrictedCamera>(RestrictedActorBP, WallToEnter->GetActorLocation(), WallToEnter->GetActorRotation());
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterWall : RestrictedActorBP has not been assigned"));
		return false;
	}
	WallPlayerPawn->AddActorLocalRotation(FRotator(90, -90, 0));
	FVector cameraDeepness = FVector(5, 10, 0);
	WallPlayerPawn->AddActorLocalOffset(cameraDeepness);
	RestrictedActor = WallPlayerPawn;

	//Repossess original actor
	//TODO: Animation should play to make the original character go into the wall
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);
	OriginalActor->SetActorLocationAndRotation(FVector(9000,9000,9500), WallPlayerPawn->GetActorRotation());
	OriginalActor->SetActorHiddenInGame(true);

	Controller->Possess(RestrictedActor);
	CurrentWall->bISPlayerInside = true;
	BPI_EnterWall();
	return true;
}

bool UBaseShadowAbility::ExitWall()
{
	//Safety check to ensure our actor is still alive and we can toggle collision back on
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OriginalActor);
	if (!ShadowComponent) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::ExitWall : No IShadowPawn"));
		return false;
	}
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);

	AController* Controller = RestrictedActor->GetController();
	if (!Controller)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::ExitWall : No Controller"));
		return false;
	}
	Controller->Possess(OriginalActor);
	//Repositioning Actor for exiting the wall
	OriginalActor->SetActorLocationAndRotation(RestrictedActor->GetActorLocation(), RestrictedActor->GetActorRotation());
	OriginalActor->AddActorWorldOffset(OriginalActor->GetActorForwardVector() * 10);//shoudl play animation for exiting
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 20));
	OriginalActor->SetActorHiddenInGame(false);

	DestroyOrHideActor(RestrictedActor);
	RestrictedActor = nullptr;
	BPI_ExitWall();
	return true;
}
void UBaseShadowAbility::EndAbility()
{
	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		Wall->OnDeath();
	}
	//Reset parameters
	AliveWalls.Empty();
	ShadowState = EAbilityState::Inactive;
	DurationTimer = -1;
	BPI_EndAbility();
}

void UBaseShadowAbility::UpdateAliveWalls()
{
	//If the main wall get's destroyed we should exit before this gets updated again. Therefore playing the other audio cue.
	bool Changed = false;
	AUShadowWall* DestroyedWall = nullptr;
	for (AUShadowWall* Wall : AliveWalls)
	{
		if (!Wall->bAlive)
		{
			DestroyedWall = Wall;
			BPI_FakeWallDestroyed();
			AliveWalls.Remove(DestroyedWall);
			Changed = true;
		}
	}

}

void UBaseShadowAbility::AbilityTickResponse(float DeltaTime)
{
	if (DurationTimer > 0)
	{
		GEngine->AddOnScreenDebugMessage(-2, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility Duration: %f"), DurationTimer, false));
		DurationTimer -= DeltaTime;
		if (DurationTimer <= 0)
		{
			EndAbility();
			return;
		}
		if (!CurrentWall->bAlive)
		{

			BPI_RealWallDestroyed();
			EndAbility();
			return;
		}
		UpdateAliveWalls();

	}
}
