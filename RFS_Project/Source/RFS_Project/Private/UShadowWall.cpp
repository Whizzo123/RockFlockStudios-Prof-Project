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
	StartWall();
}

// Called every frame
void AUShadowWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUShadowWall::StartWall()
{
	if (WallPlane)
		WallPlane->SetVisibility(false);
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No Plane Found"));


}

void AUShadowWall::ResetWall()
{
	if (WallPlane)
	{
		HitPoints = MaxHitPoints;
		WallPlane->SetVisibility(true);
	}
}
AUShadowEntrence::AUShadowEntrence() {

	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Scene Root Component");
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>("Portal Plane");
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	SetRootComponent(SceneRootComponent);
	PortalPlane->SetupAttachment(RootComponent);
	TriggerBox->SetupAttachment(RootComponent);


}
void AUShadowEntrence::BeginPlay()
{
	if (TriggerBox)
	{

		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUShadowEntrence::OverlapToggle);
		//TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUShadowEntrence::OverlapToggle);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UShadowWall: Successfully Added Begin Overlap Function"));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UShadowWall: Collision Box couldn't be created"));
}

void AUShadowEntrence::Tick(float DeltaTime)
{
}

void AUShadowEntrence::OverlapToggle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ShadowEntrence is overlapped with valid controller"));
	AController* controller = OtherActor->GetInstigatorController();
	//UFShadowAbility* ShadowComponent = Cast<UFShadowAbility>(controller->GetComponentByClass(UFShadowAbility::StaticClass()));
	if (controller)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ShadowEntrence is overlapped with valid controller"));
		//ShadowComponent->TogglePortalUseable();
	}
}

