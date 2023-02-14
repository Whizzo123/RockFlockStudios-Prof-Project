// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
	//UProperties
	UPROPERTY(EditAnywhere)
		UBehaviorTree* tree;
	//Events
	void OnPossess(APawn* InPawn) override;

};
