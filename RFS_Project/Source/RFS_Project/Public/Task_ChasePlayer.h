// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "AEnemyCharacter.h"
#include "Task_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class RFS_PROJECT_API UTask_ChasePlayer : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		bool BeginChasing(APawn* pawn, float speed);

	void OnGameplayTaskActivated(UGameplayTask& task) override {};

};
