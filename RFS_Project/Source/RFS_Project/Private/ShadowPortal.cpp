// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPortal.h"

AShadowPortal::AShadowPortal() {

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Scene Root Component");
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>("Portal Plane");
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	SetRootComponent(SceneRootComponent);
	PortalPlane->SetupAttachment(RootComponent);
	TriggerBox->SetupAttachment(RootComponent);

	//bPlayerInside = false;

}
void AShadowPortal::BeginPlay()
{
	Super::BeginPlay();
	if (TriggerBox)
	{

		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AShadowPortal::OnOverlapBegin);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AShadowPortal::OnOverlapEnd);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UShadowPortal: Successfully Added Begin Overlap Function"));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UShadowPortal: Collision Box couldn't be created"));
}

void AShadowPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShadowPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OtherActor);
	if (ShadowComponent && bPlayerInside != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UShadowPortal is overlapped with valid pawn"));
		*bPlayerInside = true;
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ShadowEntrence is overlapped with an INVALID pawn"));

	}
}

void AShadowPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IShadowPawn* ShadowComponent = Cast<IShadowPawn>(OtherActor);
	if (ShadowComponent && bPlayerInside != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UShadowPortal is no longer overlapped with valid pawn"));
		*bPlayerInside = false;
	}
	else {

	}
}

