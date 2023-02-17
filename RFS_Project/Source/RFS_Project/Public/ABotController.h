// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BrainComponent.h"
#include "AEnemyCharacter.h"
#include "ABotController.generated.h"

/**
 * 
 */
UCLASS()
class RFS_PROJECT_API ABotController : public AAIController
{
	GENERATED_BODY()

public:
	//Functions
	ABotController(const FObjectInitializer& ObjectInitializer);
	void SetDistanceToPlayer(UBlackboardComponent* board);
	////UFunctions
	UFUNCTION()
		void EventTimerUp();
	UFUNCTION(BlueprintCallable)
		void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	////UProperties
	UPROPERTY(EditAnywhere)
		UBehaviorTree* tree;
	UPROPERTY(EditAnywhere)
		float lineOfSightTime;
	UPROPERTY(EditAnywhere)
		FName lineOfSightBBKey;
	UPROPERTY(EditAnywhere)
		FName enemyActorBBKey;
	UPROPERTY(EditAnywhere)
		FName distanceToPlayerBBKey;
	UPROPERTY(EditAnywhere)
		FName playerTag;
	////Events
	void OnPossess(APawn* InPawn) override;
	void Tick(float DeltaTime) override;
	////Variables
	FTimerHandle sightLossTimer;
};
