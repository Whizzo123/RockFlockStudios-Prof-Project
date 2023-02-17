// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_ChasePlayer.h"

bool UTask_ChasePlayer::BeginChasing(APawn* pawn, float speed)
{
	AAEnemyCharacter* agent = Cast<AAEnemyCharacter>(pawn);
	if (pawn)
	{
		agent->UpdateWalkSpeed(speed);
		return true;
	}
	return false;
}