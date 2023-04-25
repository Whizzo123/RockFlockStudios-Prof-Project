// Fill out your copyright notice in the Description page of Project Settings.


#include "ABotController.h"



ABotController::ABotController()
{
	
}

void ABotController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// Bind delegate for call on pawn respawn
	AAEnemyCharacter* MyPawn = Cast<AAEnemyCharacter>(InPawn);
	MyPawn->OnRespawn.BindDynamic(this, &ABotController::ResetForRespawn);
	// Start the behaviour tree
	RunBehaviorTree(Tree);
	Board = Blackboard.Get();
}

void ABotController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{	
	if (GetTeamAttitudeTowards(*Actor) == ETeamAttitude::Hostile)
	{
		bool bSuccess = Stimulus.WasSuccessfullySensed();
		AActor* boardActor = Cast<AActor>(Board->GetValueAsObject(EnemyActorBBKey));
		// The object is it still within view or is it now exiting our view
		if (bSuccess)
		{
			// Add actor to seenObjects
			SeenObjects.Add(Actor);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Adding:" + Actor->GetName());
		}
		else
		{
			if (boardActor == Actor)
			{
				// Update blackboard that we have lost sight
				Board->SetValueAsBool(LineOfSightBBKey, false);
				// Start loss of sight timer
				GetWorld()->GetTimerManager().SetTimer(SightLossTimer, this, &ABotController::LossSightOfEnemy, LineOfSightTime, false);
			}
			// The object we just lost sight of is it still in the seen objects set
			if (SeenObjects.Contains(Actor))
			{
				// Remove the actor from our seen objects set
				SeenObjects.Remove(Actor);
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Remove:" + Actor->GetName());
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Seen Objects Left: %i"),  SeenObjects.Num()));
			}
		}
		// Do we have any targets?
		if (SeenObjects.Num() > 0)
		{
			// Have we already got a target?
			if (boardActor == nullptr)
			{
				bool caughtSightOfThePlayer = false;
				// Loop through the set
				AActor* player = SeeingPlayer();
				if (player)
				{
					SetEnemyBoardActor(player);
					//Play corresponding spotting sound
					BPI_LineOfSightPlayer();
					caughtSightOfThePlayer = true;
				}
				//We don't have the player so just lock on to the first hostile
				if (!caughtSightOfThePlayer)
				{
					AActor* firstHostileInSet = *SeenObjects.begin();
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Setting Target on wall:" + firstHostileInSet->GetName());
					SetEnemyBoardActor(firstHostileInSet);
					BPI_LineOfSightWall();
				}
			}
			// We have board actor but if we are seeing the player need to override
			else
			{
				// If our target is the player
				float const thresholdDistance = 2000.0f;
				if (boardActor->ActorHasTag(PlayerTag) && FVector::Dist(boardActor->GetActorLocation(), GetPawn()->GetActorLocation()) > thresholdDistance)
				{
					// Find another hostile or just clear the target
					if (SeenObjects.Num() <= 1)
					{
						Board->SetValueAsBool(LineOfSightBBKey, false);
						Board->SetValueAsObject(EnemyActorBBKey, nullptr);
						SeenObjects.Remove(boardActor);
					}
					else
					{
						SeenObjects.Remove(boardActor);
						SetEnemyBoardActor(*SeenObjects.begin());
					}
				}
				// Our target is a shadow wall
				else
				{
					//Have we seen the player
					AActor* player = SeeingPlayer();
					if (player && FVector::Dist(boardActor->GetActorLocation(), GetPawn()->GetActorLocation()) > thresholdDistance)
					{
						GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Switching from wall to player");
						// Switch target to player
						SetEnemyBoardActor(player);
					}
				}
			}
		}
		// If we have no hostiles that we see but still have a target
		else
		{
			// Update blackboard that we have lost sight
			Board->SetValueAsBool(LineOfSightBBKey, false);
			// Start loss of sight timer
			GetWorld()->GetTimerManager().SetTimer(SightLossTimer, this, &ABotController::LossSightOfEnemy, LineOfSightTime, false);
		}
		
	}
}

ETeamAttitude::Type ABotController::GetTeamAttitudeTowards(const AActor& Other)
{
	if (APlayerCharacter const* PlayerCharacter = Cast<APlayerCharacter>(&Other))
	{
		return ETeamAttitude::Hostile;
	}
	else if (AUShadowWall const* ShadowWall = Cast<AUShadowWall>(&Other))
	{
		if (ShadowWall->alive == true)
		{
			return ETeamAttitude::Hostile;
		}
	}
	return ETeamAttitude::Neutral;

}

void ABotController::SendHint(AActor* Actor, float HintTime)
{
	if (Actor)
	{
		// Update blackboard with enemy actor value
		Board->SetValueAsObject(EnemyActorBBKey, Actor);
		Board->SetValueAsBool(HintingBBKey, true);
		// Start hint duration timer
		GetWorld()->GetTimerManager().SetTimer(HintDurationTimer, this, &ABotController::HintTimerUp, HintTime, false);
	}
}

void ABotController::ResetForRespawn()
{
	Board->SetValueAsObject(EnemyActorBBKey, nullptr);
	Board->SetValueAsBool(LineOfSightBBKey, false);
}

void ABotController::LossSightOfEnemy()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, "Lost Sight");
	Board->SetValueAsObject(EnemyActorBBKey, nullptr);
}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Do we have a reference to the player in the scene?
	if (!LocalPlayer)
	{
		// If not attempt to grab one
		LocalPlayer = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
		if (LocalPlayer)
		{
			// If we manage to grab one set the OnAIHint delegate to call SendHit
			LocalPlayer->OnAIHint.AddDynamic(this, &ABotController::SendHint);
		}
	}
	if (AUShadowWall const* ShadowWall = Cast<AUShadowWall>(Board->GetValueAsObject(EnemyActorBBKey)))
	{
		if (ShadowWall->alive == false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Clearing wall on tick as unalive");
			SeenObjects.Remove(Cast<AActor>(Board->GetValueAsObject(EnemyActorBBKey)));
			Board->SetValueAsObject(EnemyActorBBKey, nullptr);
			Board->SetValueAsBool(LineOfSightBBKey, false);
			if (SeenObjects.Num() > 0)
			{
				AActor* target = *SeenObjects.begin();
				Board->SetValueAsObject(EnemyActorBBKey, target);
				Board->SetValueAsBool(LineOfSightBBKey, true);
			}
		}
	}
	// Update the distance to the player on the blackboard
	SetDistanceToTarget();
}

void ABotController::SetDistanceToTarget()
{
	// If we have a set enemy actor in the Blackboard
	AActor* Target = Cast<AActor>(Board->GetValueAsObject(EnemyActorBBKey));
	if (Target)
	{
		// Grab player location
		FVector Loc = Target->GetActorLocation();
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			// Calculate the distance and set it to the Blackboard
			FVector PawnLoc = ControlledPawn->GetActorLocation();
			float dist = FVector::Dist(Loc, PawnLoc);
			Board->SetValueAsFloat(DistanceToPlayerBBKey, dist);
		}
	}
}

void ABotController::HintTimerUp()
{
	if (Board->GetValueAsBool(LineOfSightBBKey) == false)
	{
		Board->SetValueAsObject(EnemyActorBBKey, nullptr);
		Board->SetValueAsBool(HintingBBKey, false);
	}
}

void ABotController::SetEnemyBoardActor(AActor* Actor)
{
	// Stop the timer for losing sight of player
	GetWorld()->GetTimerManager().ClearTimer(SightLossTimer);
	// Update blackboard values
	Board->SetValueAsBool(LineOfSightBBKey, true);
	Board->SetValueAsObject(EnemyActorBBKey, Actor);
	// Set distance to player
	SetDistanceToTarget();
}

AActor* ABotController::SeeingPlayer()
{
	for (auto iterator = SeenObjects.CreateConstIterator(); iterator; ++iterator)
	{
		AActor* seenObject = *iterator;
		// Is the object the player
		if (seenObject->ActorHasTag(PlayerTag))
		{
			return seenObject;
		}
	}
	return nullptr;
}