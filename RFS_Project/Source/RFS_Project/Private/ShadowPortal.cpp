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

	PlayerInside = false;
}
void AShadowPortal::BeginPlay()
{
	if (TriggerBox)
	{

		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AShadowPortal::OverlapToggle);
		//TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUShadowEntrence::OverlapToggle);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UShadowWall: Successfully Added Begin Overlap Function"));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UShadowWall: Collision Box couldn't be created"));
}

void AShadowPortal::Tick(float DeltaTime)
{
}

void AShadowPortal::OverlapToggle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ShadowEntrence is overlapped with valid controller"));
	AController* controller = OtherActor->GetInstigatorController();
	IIShadowPawn* ShadowComponent = dynamic_cast<IIShadowPawn*>(OtherActor);
	if (ShadowComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ShadowEntrence is overlapped with valid controller"));
		PlayerInside = false;
	}
}
