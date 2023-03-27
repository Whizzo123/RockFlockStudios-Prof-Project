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
#include "Kismet/GameplayStatics.h"
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
	ABotController();
	void SetDistanceToPlayer(UBlackboardComponent* board);
	////UFunctions
	UFUNCTION()
		void EventTimerUp();
	UFUNCTION(BlueprintCallable)
		void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintCallable)
		void SendHint(AActor* Actor, float hintTime);
	UFUNCTION()
		void HintTimerUp();
	UFUNCTION()
		void ResetForRespawn();
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
	/*void BeginPlay() override;*/
	////Variables
	FTimerHandle sightLossTimer;
	FTimerHandle hintDurationTimer;
	APlayerCharacter* local_player;


	UFUNCTION(BlueprintImplementableEvent)
		void BPI_LineOfSight();
};
