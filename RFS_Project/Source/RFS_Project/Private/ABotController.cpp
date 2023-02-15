// Fill out your copyright notice in the Description page of Project Settings.


#include "ABotController.h"




void ABotController::BeginPlay()
{
	sensesComponent = this->FindComponentByClass<UAIPerceptionComponent>();
	sensesComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABotController::HandleTargetPerceptionUpdated);
}

void ABotController::OnPossess(APawn* pawn)
{
	AAIController::OnPossess(pawn);
	bool running = RunBehaviorTree(tree);
	FString msg = pawn->GetHumanReadableName();
	if(running)
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, msg);
}

void ABotController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	bool brokenStimulus = true;
	UBlackboardComponent* board = Blackboard.Get();
	if (brokenStimulus)
	{
		GetWorld()->GetTimerManager().ClearTimer(sightLossTimer);
		board->SetValueAsBool(lineOfSightBBKey, true);
		board->SetValueAsObject(enemyActorBBKey, Actor);
		//Set distance to player
		// TODO
		// Convert BP_FirstPersonCharacter to c++ or just create dummy c++ class for code access
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
	// TODO waiting on c++ conversion of player BP
}