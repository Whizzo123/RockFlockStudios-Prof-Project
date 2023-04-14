// Fill out your copyright notice in the Description page of Project Settings.


#include "UShadowWall.h"

// Sets default values
AUShadowWall::AUShadowWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Scene Root Component");
	WallPlane = CreateDefaultSubobject<UStaticMeshComponent>("Wall Plane");

	SetRootComponent(SceneRootComponent);
	WallPlane->SetupAttachment(RootComponent);
	
}

void AUShadowWall::Spawn()
{
}

// Called when the game starts or when spawned
void AUShadowWall::BeginPlay()
{
	Super::BeginPlay();

	/*TArray<UActorComponent*> StaticComps;
	StaticComps = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	if (StaticComps.Num() > 0)
	{
		plane = Cast<UStaticMeshComponent>(StaticComps[0]);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Plane is more than 0"));
	}*/
	WallPlane->SetVisibility(false);
	ResetWall();
}

// Called every frame
void AUShadowWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUShadowWall::StartWall(int i)
{
	if (!WallPlane) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No Plane Found"));
		return;
	}
	ChangeWallTextures(i);
	WallPlane->SetVisibility(true);
	alive = true;

}

void AUShadowWall::ResetWall()
{
	if (WallPlane)
	{
		HitPoints = MaxHitPoints;
		alive = false;
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Plane not reset"));
	}
}

