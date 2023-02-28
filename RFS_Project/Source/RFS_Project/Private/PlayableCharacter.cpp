// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

