// Fill out your copyright notice in the Description page of Project Settings.


#include "ARestrictedCamera.h"

// Sets default values
AARestrictedCamera::AARestrictedCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Scene Root Component");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");

	SetRootComponent(SceneRootComponent);
	CameraComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AARestrictedCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARestrictedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARestrictedCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

