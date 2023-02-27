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
	_skeletalMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
}

void AAGun::Fire()
{
	if (_skeletalMesh)
	{
		FVector skeletalSocketLoc = _skeletalMesh->GetSocketLocation(fireSocket);
		FVector accOffset = CalculateAccuracy();
		FRotator rotation;
		if (playerGun)
			rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
		else
			rotation = GetActorRightVector().Rotation();
		FVector offset = rotation.RotateVector(projectileOffset);
		FVector spawnLoc = offset + skeletalSocketLoc;
		FRotator finalRot = rotation.Add(0.0f, accOffset.Y, 0.0f);
		//GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, accOffset.ToString());
		FTransform transform = FTransform(finalRot, spawnLoc, FVector(1.0f, 1.0f, 1.0f));
		AAGunProjectile* spawned = GetWorld()->SpawnActor<AAGunProjectile>(projectileToFire->GetDefaultObject()->GetClass(),
			transform);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSoundFX, spawnLoc);
	}
	else
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, "YOUVE FORGOTTEN A SKELETAL MESH ON THE GUN OBJECT");
}

FVector AAGun::CalculateAccuracy()
{
	int random = rand() % 4;
	//TODO introduce accuracy var back in
	if (random < 2)
	{
		return trajectoryOffset * (10 - rand () % 10);
	}
	else
	{
		return trajectoryOffset * (10 + rand () % 10);
	}
}
