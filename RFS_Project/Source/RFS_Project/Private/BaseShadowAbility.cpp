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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::DestroyOrHideActor : Couldn't destroy actor, attempting to hide"));
		}
		else 
		{
			Actor->AddActorWorldOffset(FVector(0, 500, 0));
			Actor->SetActorHiddenInGame(true);
		}
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FShadowAbility::DestroyOrHideActor : Actor does not exist"));

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
			bSuccess = ActiveState();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: Current State %i was %i"), int(ShadowState), bSuccess));
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
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility:: moving onto state %i"), int(ShadowState)));
		return true;
	}
	return false;
}

TSet<AUShadowWall*> UBaseShadowAbility::SphereCastWalls(FVector Origin)
{
	TSet<AUShadowWall*> ShadowWalls;
	FCollisionQueryParams TraceParams;
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel(Hits, Origin, Origin, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(WallDetectionRange), TraceParams);

	//Goes through all objects hit adn grabs the walls and adds them to TSet
	for (int i = 0; i < Hits.Num(); i++)
	{
		AUShadowWall* Wall = Cast<AUShadowWall>(Hits[i].GetActor());
		if (Wall) {
			ShadowWalls.Add(Wall);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FShadowAbility::SphereCastWalls: Walls found %i"), ShadowWalls.Num()));
	return ShadowWalls;

}
TSet<AUShadowWall*> UBaseShadowAbility::DiscCastWalls(FVector origin) {
	TArray<FHitResult> Hits;
	TSet<AUShadowWall*> ShadowWalls;

	//360 degrees of line tracing to detect and add AUShadowWalls //TODO: If the wall is currently in use, do not add it
	for (int i = 1; i < DiscAccuracy; i++)
	{
		FVector EndVector(1, 0, 0);
		float YawAmount = ((360 / DiscAccuracy) * i);
		EndVector = EndVector.RotateAngleAxis(YawAmount, FVector3d(0, 0, 1));
		EndVector *= WallDetectionRange;
		GetWorld()->LineTraceMultiByChannel(Hits, origin, origin + EndVector, ECC_Visibility);

		//Go through all actors hit and add relevant ones
		for (int Actors = 0; Actors < Hits.Num(); Actors++)
		{
			AUShadowWall* Wall = Cast<AUShadowWall>(Hits[Actors].GetActor());
			if (Wall)
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
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("FShadowAbility::SphereCastWalls: Invalid Wall at : Index %i , Num %i , Valid %i"), Index, Num, Valid));

		}
	}
	return NewWalls;

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
	OriginalActor->SetActorLocationAndRotation(WallPlayerPawn->GetActorLocation(), WallPlayerPawn->GetActorRotation());
	OriginalActor->AddActorWorldOffset(FVector(0, 0, 500));
	OriginalActor->SetActorHiddenInGame(true);

	Controller->Possess(RestrictedActor);

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
	OriginalActor->AddActorWorldOffset(OriginalActor->GetActorForwardVector() * 300);//shoudl play animation for exiting
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
	ShadowState = EAbilityState::Inactive;
	DurationTimer = Duration;
	BPI_EndAbility();
}