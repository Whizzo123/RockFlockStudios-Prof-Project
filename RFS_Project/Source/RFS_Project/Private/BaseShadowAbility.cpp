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
		return FVector(0, 1, 0);
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

bool UBaseShadowAbility::Use_Implementation()
{
	//Template for Shadow Abilities to use
	if (!OriginalActor)
	{
		return false;
	}


	bool bNextState = false;
	switch (ShadowState)
	{
		case EAbilityState::Inactive:
		{
			bNextState = InactiveState();
			break;
		}
		case EAbilityState::Cue:
		{
			bNextState = CueState();
			break;
		}
		case EAbilityState::Active:
		{
			bNextState = ActiveState();
			break;
		}
		default:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility: Invalid State"));
			break;
		}
	}


	if (bNextState)
	{
		AdvanceState();
		return true;
	}
	else if (!bNextState && ShadowState != EAbilityState::Active)
	{
		ShadowState = EAbilityState::Inactive;
		return false;
	}
	else if(!bNextState)
	{
		return true;
	}
	return false;
}
void UBaseShadowAbility::AdvanceState()
{
	if (ShadowState != EAbilityState::Active)
	{
		ShadowState = EAbilityState(int(ShadowState) + 1);
	}
}
TSet<AUShadowWall*> UBaseShadowAbility::SphereCastWalls(FVector Origin, float SphereRange)
{
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel(Hits, Origin, Origin, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(SphereRange));
	return GetValidWallsFromHits(Hits);

}
TSet<AUShadowWall*> UBaseShadowAbility::DiscCastWalls(FVector Origin) {
	TSet<AUShadowWall*> ShadowWalls;

	//360 degrees of line tracing to detect and add AUShadowWalls
	for (int i = 1; i < DiscAccuracy; i++)
	{
		TArray<FHitResult> Hits;
		FVector EndVector(1, 0, 0);
		float YawAmount = ((360 / DiscAccuracy) * i);
		EndVector = EndVector.RotateAngleAxis(YawAmount, FVector3d(0, 0, 1));//Rotates linetrace in a 360 around player 
		EndVector *= WallDetectionRange;

		//Note: There has been no way to continue a trace while the player body is inside it(for FShadowAbility not FShadowAbility1)
		GetWorld()->LineTraceMultiByChannel(Hits, Origin, Origin + EndVector, ECC_Visibility);
		ShadowWalls.Append(GetValidWallsFromHits(Hits));
	}
	return ShadowWalls;
}
TSet<AUShadowWall*> UBaseShadowAbility::ChooseWalls(TSet<AUShadowWall*> ShadowWalls)
{
	TArray<AUShadowWall*> Walls = ShadowWalls.Array();
	TSet<AUShadowWall*> NewWalls = TSet<AUShadowWall*>();
	if (Walls.Num() == 0)
	{
		return NewWalls;
	}


	//We start at 1 to account for the CurrentWall at 0
	for (int i = 1; i < WallAmount; i++)
	{
		//Get a random index from Walls
		int Num = Walls.Num();
		int Index = FMath::RandRange(0, Num - 1);
		bool Valid = Walls.IsValidIndex(Index);
		//Choose a random wall
		if (Valid)
		{
			NewWalls.Add(Walls[Index]);
			Walls.RemoveAt(Index, 1, true);
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
	// Call to send hint to the AI
	if (APlayerCharacter* player = Cast<APlayerCharacter>(OriginalActor))
	{
		int idx = rand() % AliveWalls.Num();
		auto it = AliveWalls.begin();
		for (int i = 0; i < idx; i++)
		{
			++it;
		}
		AUShadowWall* wallForHint = *it;
		player->CreateHint(wallForHint, 5.0f);
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
	//Spawn and assign RestrictedCharacter
	AARestrictedCamera* WallPlayerPawn;
	if (RestrictedActorBP)
	{
		WallPlayerPawn = GetWorld()->SpawnActor<AARestrictedCamera>(RestrictedActorBP, WallToEnter->GetActorLocation(), WallToEnter->GetActorRotation());
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::EnterWall : RestrictedActorBP has not been assigned"));
		return false;
	}
	//Reposition Actor to be within walls
	WallPlayerPawn->AddActorLocalRotation(FRotator(90, -90, 0));
	FVector CameraDeepness = FVector(5, 10, 0);
	WallPlayerPawn->AddActorLocalOffset(CameraDeepness);
	RestrictedActor = WallPlayerPawn;

	//Ensures original actor cannot be targeted or seen
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);//Character cannot get damaged
	OriginalActor->SetActorLocation(FVector(9000,9000,9500));
	OriginalActor->SetActorHiddenInGame(true);

	AController* Controller = OriginalActor->GetController();
	Controller->Possess(RestrictedActor);
	CurrentWall->bISPlayerInside = true;
	bInsideWalls = true;
	BPI_EnterWall();
	return true;
}

bool UBaseShadowAbility::ExitWall()
{
	if (!RestrictedActor)
	{
		return false;
	}
	//Repositioning Actor for exiting the wall
	OriginalActor->SetActorLocationAndRotation(RestrictedActor->GetActorLocation(), RestrictedActor->GetActorRotation());
	OriginalActor->AddActorWorldOffset(OriginalActor->GetActorForwardVector() * 10);//shoudl play animation for exiting
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 20));
	OriginalActor->SetActorHiddenInGame(false);
	IShadowPawn::Execute_ToggleCollisionPhysics(OriginalActor);

	AController* Controller = RestrictedActor->GetController();
	Controller->Possess(OriginalActor);
	DestroyOrHideActor(RestrictedActor);
	RestrictedActor = nullptr;

	BPI_ExitWall();
	CurrentWall->bISPlayerInside = false;
	bInsideWalls = false;
	DurationTimer = DurationEndStart;
	return true;
}
void UBaseShadowAbility::EndAbility()
{
	//Exit's wall if we are in it, destroys portal if it's active
	if (ShadowState == EAbilityState::Active && bInsideWalls) 
	{
		ExitWall();
	}

	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		if (Wall->IsAlive())
		{
			Wall->EndWall();
		}
	}
	//Reset parameters
	ShadowState = EAbilityState::Inactive;
	DurationTimer = -1;
	bInsideWalls = false;
	BPI_EndAbility();
}

void UBaseShadowAbility::EndAbilityAbrupt()
{
	//Exit's wall if we are in it
	if (ShadowState == EAbilityState::Active && bInsideWalls) 
	{
		ExitWall();
	}

	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		if (Wall->IsAlive())
		{
			AUShadowWall::Execute_OnDeath(Wall);

		}
	}
	//Reset parameters
	ShadowState = EAbilityState::Inactive;
	DurationTimer = -1;
	bInsideWalls = false;
	BPI_RealWallDestroyed();
}

void UBaseShadowAbility::UpdateAliveWalls()
{
	//If the main wall get's destroyed we should exit before this gets updated again. Therefore playing the other audio cue.
	for (AUShadowWall* Wall : AliveWalls)
	{
		if (!Wall->IsAlive())
		{
			BPI_FakeWallDestroyed();
			AliveWalls.Remove(Wall);
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
		if (!CurrentWall->IsAlive())
		{

			EndAbilityAbrupt();
			return;
		}

		UpdateAliveWalls();
	}
}



TSet<AUShadowWall*> UBaseShadowAbility::GetValidWallsFromHits(TArray<FHitResult> Hits)
{
	TSet<AUShadowWall*> ShadowWalls;
	for (int Actors = 0; Actors < Hits.Num(); Actors++)
	{

		AUShadowWall* Wall = Cast<AUShadowWall>(Hits[Actors].GetActor());
		if (Wall && !Wall->bInUse)
		{
			ShadowWalls.Add(Wall);
		}
	}
	return ShadowWalls;
}

void UBaseShadowAbility::AbortAll()
{

	TurnOffVisibleWalls();

	if (ShadowState == EAbilityState::Active && bInsideWalls)
	{
		ExitWall();
	}

	//Destroy walls
	for (AUShadowWall* Wall : AliveWalls)
	{
		if (Wall->IsAlive())
		{
			AUShadowWall::Execute_OnDeath(Wall);

		}
	}

	AliveWalls.Empty();
	CurrentWall = nullptr;
	ShadowState = EAbilityState::Inactive;
	DurationTimer = -1;
	bInsideWalls = false;
}
