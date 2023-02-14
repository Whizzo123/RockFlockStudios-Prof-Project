// Fill out your copyright notice in the Description page of Project Settings.


#include "ABotController.h"


void ABotController::OnPossess(APawn* pawn)
{
	AAIController::OnPossess(pawn);
	bool running = RunBehaviorTree(tree);
	FString msg = pawn->GetHumanReadableName();
	if(running)
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, msg);
}