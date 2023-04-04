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
}

void ABotController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (GetTeamAttitudeTowards(*Actor) == ETeamAttitude::Hostile)
	{
		bool bIsPlayer = Actor->ActorHasTag(PlayerTag);
		bool bSuccess = Stimulus.WasSuccessfullySensed();
		UBlackboardComponent* Board = Blackboard.Get();
		// Have we successfully sensed and is it the player we saw?
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Actor->GetFName().ToString());
		if (bIsPlayer && bSuccess)
		{
			// Stop the timer for losing sight of player
			GetWorld()->GetTimerManager().ClearTimer(SightLossTimer);
			// Update blackboard values
			Board->SetValueAsBool(LineOfSightBBKey, true);
			Board->SetValueAsObject(EnemyActorBBKey, Actor);
			// Set distance to player
			SetDistanceToPlayer(Board);
			BPI_LineOfSight();
		}
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
	else
	{
		return ETeamAttitude::Neutral;
	}
}

void ABotController::SendHint(AActor* Actor, float HintTime)
{
	UBlackboardComponent* Board = Blackboard.Get();
	if (Actor)
	{
		// Update blackboard with enemy actor value
		Board->SetValueAsObject(EnemyActorBBKey, Actor);
		// Start hint duration timer
		GetWorld()->GetTimerManager().SetTimer(HintDurationTimer, this, &ABotController::HintTimerUp, HintTime, false);
	}
}

void ABotController::ResetForRespawn()
{
	UBlackboardComponent* Board = Blackboard.Get();
	Board->SetValueAsObject(EnemyActorBBKey, nullptr);
	Board->SetValueAsBool(LineOfSightBBKey, false);
}

void ABotController::LossSightOfEnemy()
{
	UBlackboardComponent* Board = Blackboard.Get();
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
	// Update the distance to the player on the blackboard
	SetDistanceToPlayer(Blackboard.Get());
}

void ABotController::SetDistanceToPlayer(UBlackboardComponent* Board)
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
	UBlackboardComponent* Board = Blackboard.Get();
	if (Board->GetValueAsBool(LineOfSightBBKey) == false)
	{
		Board->SetValueAsObject(EnemyActorBBKey, nullptr);
	}
}