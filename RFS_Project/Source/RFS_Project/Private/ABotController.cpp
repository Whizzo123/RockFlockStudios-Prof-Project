// Fill out your copyright notice in the Description page of Project Settings.


#include "ABotController.h"


ABotController::ABotController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ABotController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	RunBehaviorTree(tree);
}

void ABotController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	bool isPlayer = Actor->ActorHasTag(playerTag);
	bool success = Stimulus.WasSuccessfullySensed();
	UBlackboardComponent* board = Blackboard.Get();
	if (isPlayer && success)
	{
		GetWorld()->GetTimerManager().ClearTimer(sightLossTimer);
 		board->SetValueAsBool(lineOfSightBBKey, true);
		board->SetValueAsObject(enemyActorBBKey, Actor);
		//Set distance to player
		SetDistanceToPlayer(board);
	}
	else
		GetWorld()->GetTimerManager().SetTimer(sightLossTimer, this, &ABotController::EventTimerUp, lineOfSightTime, false);
}

void ABotController::EventTimerUp()
{
	UBlackboardComponent* board = Blackboard.Get();
	board->SetValueAsBool(lineOfSightBBKey, false);
	board->SetValueAsObject(enemyActorBBKey, nullptr);
}

void ABotController::Tick(float DeltaTime)
{
	SetDistanceToPlayer(Blackboard.Get());
}

void ABotController::SetDistanceToPlayer(UBlackboardComponent* board)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(board->GetValueAsObject(enemyActorBBKey));
	if (player)
	{
		FVector loc = player->GetActorLocation();
		APawn* controlledPawn = GetPawn();
		if (controlledPawn)
		{
			FVector pawnLoc = controlledPawn->GetActorLocation();
			float dist = FVector::Dist(loc, pawnLoc);
			board->SetValueAsFloat(distanceToPlayerBBKey, dist);
		}
	}
}