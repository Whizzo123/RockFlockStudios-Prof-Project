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
		FVector offset = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation().RotateVector(projectileOffset);
		FVector spawnLoc = offset + skeletalSocketLoc;
		FTransform transform = FTransform(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation(),
			spawnLoc, FVector(1.0f, 1.0f, 1.0f));
		AAGunProjectile* spawned = GetWorld()->SpawnActor<AAGunProjectile>(projectileToFire->GetDefaultObject()->GetClass(), transform);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSoundFX, spawnLoc);
	}
	else
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, "YOUVE FORGOTTEN A SKELETAL MESH ON THE GUN OBJECT");
}

