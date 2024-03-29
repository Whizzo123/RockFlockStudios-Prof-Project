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
#include "UShadowWall.h"
#include "Kismet/GameplayStatics.h"
#include "ABotController.generated.h"


UCLASS()
/* A class for the base functionality for the controller of the combat version of the AI*/
class RFS_PROJECT_API ABotController : public AAIController
{
	GENERATED_BODY()

public:
	/*
	* Called when we possess a pawn 
	* @param APawn - Pawn that is being possessed
	*/
	void OnPossess(APawn* InPawn) override;
	/*
	* Called every tick of the game world
	* @param DeltaTime - Time between ticks
	*/
	void Tick(float DeltaTime) override;
	/*Default Constructor*/
	ABotController();
	/*
	* Sets the distanceToPlayer key in the AI blackboard
	* @param Board - Blackboard to set value on
	*/
	void SetDistanceToTarget();
	/* Function called for getting the AI's team alignment*/
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other);
	/* Called to have AI lose focus on enemy*/
	UFUNCTION()
		void LossSightOfEnemy();
	/*
	* Blueprint-callable function to deal with updates to line of sight on any enemies
	* @param Actor - Actor we have just caught sight of
	* @param Stimulus - Sense component that prompted the call in this case sight
	*/
	UFUNCTION(BlueprintCallable)
		void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	/*
	* Blueprint-callable function to send a hint to the AI of a location they should investigate
	* @param Actor - Actor the AI should move towards
	* @param HintTime - Time to let the AI use the hint for
	*/
	UFUNCTION(BlueprintCallable)
		void SendHint(AActor* Actor, float HintTime);
	/*Blueprint-implementable event for when AI sees player*/
	UFUNCTION(BlueprintImplementableEvent)
		void BPI_LineOfSightPlayer();	
	/*Blueprint-implementable event for when AI sees Shadow Wall*/
	UFUNCTION(BlueprintImplementableEvent)
		void BPI_LineOfSightWall();
	/* Called when the time for the current hint is up*/
	UFUNCTION()
		void HintTimerUp();
	/* Called to reset AI properties on respawn after death*/
	UFUNCTION()
		void ResetForRespawn();
	void UpdateAITarget();
private:
	void SetEnemyBoardActor(AActor* Actor);
	AActor* SeeingPlayer();
public:
	/* Reference to the given behaviour tree to use*/
	UPROPERTY(EditAnywhere)
		UBehaviorTree* Tree;
	/*Value for how long we track enemy after losing sight*/
	UPROPERTY(EditAnywhere)
		float LineOfSightTime;
	/*FName value for referencing LineOfSight in blackboard*/
	UPROPERTY(EditAnywhere)
		FName LineOfSightBBKey;
	/*FName value for referencing EnemyActor in blackboard*/
	UPROPERTY(EditAnywhere)
		FName EnemyActorBBKey;
	/*FName value for referencing DistanceToPlayer in blackboard*/
	UPROPERTY(EditAnywhere)
		FName DistanceToPlayerBBKey;
	/*FName value for referencing Hinting in blackboard*/
	UPROPERTY(EditAnywhere)
		FName HintingBBKey;
	/*FName value for referencing the tag on the Player actor*/
	UPROPERTY(EditAnywhere)
		FName PlayerTag;
	/*Timer for losing sight of player*/
	FTimerHandle SightLossTimer;
	/*Timer for duration of current hint*/
	FTimerHandle HintDurationTimer;
	/*Reference to the player in the scene*/
	APlayerCharacter* LocalPlayer;
	TSet<AActor*> SeenObjects;
protected:
	/* Local reference to the behavior trees' blackboard */
	UBlackboardComponent* Board;
};
