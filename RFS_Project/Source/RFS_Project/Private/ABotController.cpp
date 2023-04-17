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
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, Actor->GetFName().ToString());
		AActor* boardActor = Cast<AActor>(Board->GetValueAsObject(EnemyActorBBKey));
		bool bSuccess = Stimulus.WasSuccessfullySensed();
		// If we have an actor already set and its the player don't set it again
		if(boardActor != nullptr && boardActor->ActorHasTag(PlayerTag) && bSuccess)
		{
			return;
		}
		// Otherwise this means we don't have the player and we are seeing a wall
		else
		{
			// Have we successfully sensed and is it the player we saw?
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Actor->GetFName().ToString());
			if (bSuccess)
			{
				// Stop the timer for losing sight of player
				GetWorld()->GetTimerManager().ClearTimer(SightLossTimer);
				// Update blackboard values
				Board->SetValueAsBool(LineOfSightBBKey, true);
				Board->SetValueAsObject(EnemyActorBBKey, Actor);
				// Set distance to player
				SetDistanceToPlayer();
				//Play corresponding spotting sound
				if (Cast<AUShadowWall>(Actor))
				{
					BPI_LineOfSightWall();
				}
				else 
				{
					BPI_LineOfSightPlayer();
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Losing Sight: " + Actor->GetFName().ToString());
				// Update blackboard that we have lost sight
				Board->SetValueAsBool(LineOfSightBBKey, false);
				// Start loss of sight timer
				GetWorld()->GetTimerManager().SetTimer(SightLossTimer, this, &ABotController::LossSightOfEnemy, LineOfSightTime, false);
			}
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
			Board->SetValueAsObject(EnemyActorBBKey, nullptr);
			Board->SetValueAsBool(LineOfSightBBKey, false);
		}
	}
	// Update the distance to the player on the blackboard
	SetDistanceToPlayer();
}

void ABotController::SetDistanceToPlayer()
{
	// If we have a set enemy actor in the Blackboard
	APlayerCharacter* Player = Cast<APlayerCharacter>(Board->GetValueAsObject(EnemyActorBBKey));
	if (Player)
	{
		// Grab player location
		FVector Loc = Player->GetActorLocation();
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