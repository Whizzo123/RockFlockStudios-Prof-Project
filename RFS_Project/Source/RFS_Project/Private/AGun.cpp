// Fill out your copyright notice in the Description page of Project Settings.


#include "AGun.h"

// Sets default values
AAGun::AAGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAGun::BeginPlay()
{
	Super::BeginPlay();
}

FVector AAGun::Fire(FVector startHitScanLoc)
{
	FVector accOffset = CalculateAccuracy();
	FRotator rotation;
	if (playerGun)
		rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	else
		rotation = GetActorRightVector().Rotation();
	FVector lineVector;
	if (playerGun)
		lineVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * 2000.0f;
	else
		lineVector = GetActorRightVector() * 2000.0f;
	AActor* hitActor = Trace<IHealth>(startHitScanLoc, (startHitScanLoc + lineVector) + (accOffset) * 20);
	if (hitActor)
	{
		IHealth* healthObj = dynamic_cast<IHealth*>(Cast<APlayableCharacter>(hitActor));
		if(playerGun)
			healthObj->OnDamage(1.0f, pawnEquippedTo);
		else
			healthObj->OnDamage(10.0f, pawnEquippedTo);
		return hitActor->GetActorLocation();
	}
	return FVector();
}

void AAGun::ApplyRecoil(ACharacter* playerCharacter, float recoilAngleYaw, float recoilAnglePitch)
{
	playerCharacter->AddControllerYawInput(recoilAngleYaw);
	playerCharacter->AddControllerPitchInput(recoilAnglePitch);
}

template<typename T>
AActor* AAGun::Trace(FVector startTrace, FVector endTrace)
{
	TArray<FHitResult> hit;
	GetWorld()->LineTraceMultiByChannel(hit, startTrace, endTrace, ECollisionChannel::ECC_Visibility);
	if(!playerGun)
		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Red, false, 1.0f);
	for (int i = 0; i < hit.Num(); i++)
	{

		AActor* hitActor = hit[i].GetActor();
		if (hitActor)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, hitActor->GetFName().ToString());
			//Check that the thing is hittable
			T* healthObj = dynamic_cast<T*>(Cast<APlayableCharacter>(hit[i].GetActor()));
			
			if (healthObj && hitActor != pawnEquippedTo)
			{
				//if(playerGun)
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, hitActor->GetFName().ToString());
				return hitActor;
			}
		}
	}
	return nullptr;
}

FVector AAGun::CalculateAccuracy()
{
	int random = rand() % 4;
	int convertedAccuracy = 1 - gunAccuracy;
	int offsetScale = 10, maximumVelocityOffset = 300;
	int currentVelocity = pawnEquippedTo->GetVelocity().Length();
	
	int movingOffset;
	int velocityPercentage = (currentVelocity / maximumVelocityOffset);
	if (velocityPercentage == 0)
	{
		movingOffset = 0;
	}
	else
		movingOffset = 2 - (2 / velocityPercentage) / 10;
	int calculatedOffset = rand() % (offsetScale - (int)((gunAccuracy - movingOffset) * offsetScale));
	if (random < 2)
	{
		return trajectoryOffset * -calculatedOffset;
	}
	else
	{
		return trajectoryOffset * calculatedOffset;
	}
}
