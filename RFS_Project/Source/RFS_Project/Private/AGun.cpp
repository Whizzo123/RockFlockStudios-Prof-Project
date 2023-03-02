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
	_skeletalMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
}

void AAGun::Fire()
{
	if (_skeletalMesh)
	{
		FVector skeletalSocketLoc = _skeletalMesh->GetSocketLocation(fireSocket);
		FVector accOffset = CalculateAccuracy();
		FRotator rotation;

		//Issues being caused
		if (playerGun)
			rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
		else
			rotation = GetActorRightVector().Rotation();
		FVector offset = rotation.RotateVector(projectileOffset);
		FVector spawnLoc = offset + skeletalSocketLoc;
		FRotator finalRot = rotation.Add(0.0f, accOffset.Y, 0.0f);
		FTransform transform = FTransform(finalRot, spawnLoc, FVector(1.0f, 1.0f, 1.0f));
		//AAGunProjectile* spawned = GetWorld()->SpawnActor<AAGunProjectile>(projectileToFire->GetDefaultObject()->GetClass(), transform);
		//use line cast instead now
		FHitResult hit;
		//FVector endPoint = FVector(1000.0f, 1000.0f, 1000.0f);finalRot.RotateVector(endPoint)
		FVector temp;
		if (playerGun)
			temp = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * 2000.0f;
		else
			temp = GetActorRightVector() * 2000.0f;
		// was spawnLoc + temp
		GetWorld()->LineTraceSingleByChannel(hit, spawnLoc, (spawnLoc + temp) + (accOffset * 100), ECollisionChannel::ECC_Pawn);
		DrawDebugLine(GetWorld(), spawnLoc, (spawnLoc + temp) + (accOffset * 100), FColor::Red, false, 10.0f);
		AActor* hitActor = hit.GetActor();
		if (hitActor)
		{
			//Check that the thing is hittable
			IHealth* healthObj = dynamic_cast<IHealth*>(Cast<APlayableCharacter>(hit.GetActor()));
			GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, hitActor->GetFName().ToString());
			if (healthObj && hitActor != pawnEquippedTo)
			{
				healthObj->OnDamage(1.0f);
				GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, "HITTING");
			}
		}
		//--------------------------
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSoundFX, spawnLoc);
	}
	else
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, "YOUVE FORGOTTEN A SKELETAL MESH ON THE GUN OBJECT");
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
	GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Yellow, FString::Printf(TEXT("%lld"), calculatedOffset));
	if (random < 2)
	{
		return trajectoryOffset * -calculatedOffset;
	}
	else
	{
		return trajectoryOffset * calculatedOffset;
	}
}
