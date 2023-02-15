// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	ABotController() {};
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	//UFunctions
	UFUNCTION()
		void EventTimerUp();
	//UProperties
	UPROPERTY(EditAnywhere)
		UBehaviorTree* tree;
	UPROPERTY(BlueprintReadWrite)
		float lineOfSightTime;
	UPROPERTY(BlueprintReadWrite)
		FName lineOfSightBBKey;
	UPROPERTY(BlueprintReadWrite)
		FName enemyActorBBKey;
	//Events
	void OnPossess(APawn* InPawn) override;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	//Variables
	UAIPerceptionComponent* sensesComponent;
	FTimerHandle sightLossTimer;

};
