// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPortal.h"

AShadowPortal::AShadowPortal() {

	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Scene Root Component");
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>("Portal Plane");
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	SetRootComponent(SceneRootComponent);
	PortalPlane->SetupAttachment(RootComponent);
	TriggerBox->SetupAttachment(RootComponent);

	bPlayerInside = false;

}
void AShadowPortal::BeginPlay()
{
	if (TriggerBox)
	{

		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AShadowPortal::OnOverlapBegin);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AShadowPortal::OnOverlapEnd);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UShadowWall: Successfully Added Begin Overlap Function"));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UShadowWall: Collision Box couldn't be created"));
}

void AShadowPortal::Tick(float DeltaTime)
{
}

void AShadowPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OtherActor);
	if (ShadowComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ShadowEntrence is overlapped with valid pawn"));
		*bPlayerInside = !*bPlayerInside;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ShadowEntrence is overlapped with an INVALID pawn"));

	}
}

void AShadowPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OtherActor);
	if (ShadowComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ShadowEntrence is no longer overlapped with valid pawn"));
		*bPlayerInside = !*bPlayerInside;
	}
	else {

	}
}

