// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AGunProjectile.h"
#include "AGun.generated.h"

UCLASS()
class RFS_PROJECT_API AAGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGun();
	void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		float gunAccuracy;
	UPROPERTY(EditAnywhere)
		float gunFirerate;
	UPROPERTY(EditAnywhere)
		float projectileSpeed;
	UPROPERTY(EditAnywhere)
		FName fireSocket;
	UPROPERTY(EditAnywhere)
		FVector projectileOffset;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAGunProjectile> projectileToFire;
	UPROPERTY(EditAnywhere)
		USoundBase* fireSoundFX;
	UPROPERTY(EditAnywhere)
		bool playerGun;
protected:
	USkeletalMeshComponent* _skeletalMesh;
	FVector CalculateAccuracy();
	FVector trajectoryOffset = FVector(0.0f, 1.0f, 0.0f);
public:	
	UFUNCTION(BlueprintCallable)
		void Fire();
};
