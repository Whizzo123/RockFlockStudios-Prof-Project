// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AGunProjectile.h"
#include "../Combat.h"
#include "DrawDebugHelpers.h"
#include "PlayableCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "AGun.generated.h"

UCLASS()
class RFS_PROJECT_API AAGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGun();
	void BeginPlay() override;
	
	// EDITOR VARIABLES
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
	// BLUEPRINT PROPERTIES
	UPROPERTY(BlueprintReadWrite)
		APawn* pawnEquippedTo;
	UPROPERTY(BlueprintReadWrite)
		FVector muzzlePoint;
	UPROPERTY(BlueprintReadOnly)
		float appliedYawRecoil;
	UPROPERTY(BlueprintReadOnly)
		float appliedPitchRecoil;
	UPROPERTY(BlueprintReadWrite)
		float waitRecoilTime;
protected:
	USkeletalMeshComponent* _skeletalMesh;
	FVector trajectoryOffset = FVector(1.0f, 0.0f, 0.0f);
	FVector CalculateAccuracy();
	template<typename T>
	AActor* Trace(FVector startTrace, FVector endTrace);
	FTimerHandle waitRecoilTimer;
	
	
	
public:	
	UFUNCTION(BlueprintCallable)
		FVector Fire(FVector startHitScanLoc);
	UFUNCTION(BlueprintCallable)
		void ApplyRecoil(ACharacter* playerCharacter, float recoilAngleYaw, float recoilAnglePitch);
	UFUNCTION()
		void ResetCameraAfterRecoil();
};
