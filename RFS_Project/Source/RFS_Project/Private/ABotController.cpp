// Fill out your copyright notice in the Description page of Project Settings.


#include "ABotController.h"



ABotController::ABotController()
{
	
}

//void ABotController::BeginPlay()
//{
//	//APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
//	//player->OnAIHint.AddDynamic(this, &ABotController::SendHint);
//}

void ABotController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	AAEnemyCharacter* my_Pawn = Cast<AAEnemyCharacter>(pawn);
	my_Pawn->OnRespawn.BindDynamic(this, &ABotController::ResetForRespawn);
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
		BPI_LineOfSight();
	}
	else
	{
		board->SetValueAsBool(lineOfSightBBKey, false);
		GetWorld()->GetTimerManager().SetTimer(sightLossTimer, this, &ABotController::EventTimerUp, lineOfSightTime, false);
	}
}

void ABotController::SendHint(AActor* Actor, float hintTime)
{
	UBlackboardComponent* board = Blackboard.Get();
	if (Actor)
	{
		board->SetValueAsObject(enemyActorBBKey, Actor);
		GetWorld()->GetTimerManager().SetTimer(hintDurationTimer, this, &ABotController::HintTimerUp, hintTime, false);
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, "Sending Hint");
	}
}

void ABotController::ResetForRespawn()
{
	UBlackboardComponent* board = Blackboard.Get();
	board->SetValueAsObject(enemyActorBBKey, nullptr);
}

void ABotController::EventTimerUp()
{
	UBlackboardComponent* board = Blackboard.Get();
	board->SetValueAsObject(enemyActorBBKey, nullptr);
}

void ABotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!local_player)
	{
		local_player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
		if(local_player)
			local_player->OnAIHint.AddDynamic(this, &ABotController::SendHint);
	}
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

void ABotController::HintTimerUp()
{
	UBlackboardComponent* board = Blackboard.Get();
	if(board->GetValueAsBool(lineOfSightBBKey) == false)
		board->SetValueAsObject(enemyActorBBKey, nullptr);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, "Hint Timer Up");
}