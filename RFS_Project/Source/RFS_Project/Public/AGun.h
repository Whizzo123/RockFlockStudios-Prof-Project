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
		float GunAccuracy;
	UPROPERTY(EditAnywhere)
		float GunFirerate;
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed;
	UPROPERTY(EditAnywhere)
		FName FireSocket;
	UPROPERTY(EditAnywhere)
		FVector ProjectileOffset;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAGunProjectile> ProjectileToFire;
	UPROPERTY(EditAnywhere)
		USoundBase* FireSoundFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayerGun;
	UPROPERTY(EditAnywhere)
		float GunRange;
	// BLUEPRINT PROPERTIES
	UPROPERTY(BlueprintReadWrite)
		APawn* PawnEquippedTo;
	UPROPERTY(BlueprintReadWrite)
		FVector MuzzlePoint;

protected:
	FVector TrajectoryOffset = FVector(1.0f, 0.0f, 0.0f);
	/// <summary>
	/// Calculates the accuracy of the guns shot
	/// </summary>
	/// <returns>The offset vector for the shot</returns>
	FVector CalculateAccuracy();
	/// <summary>
	/// Completes a multi raycast for a component of the given type
	/// </summary>
	/// <typeparam name="T">Type to raycast for</typeparam>
	/// <param name="StartTrace">Start point of the trace</param>
	/// <param name="EndTrace">End point of the trace</param>
	/// <returns>The first hit object of that type of the trace or if none found returns just the first hit actor</returns>
	template<typename T>
	AActor* Trace(FVector StartTrace, FVector EndTrace);
	
public:	
	/// <summary>
	/// Blueprint-callable function that tells the gun to fire
	/// </summary>
	UFUNCTION(BlueprintCallable)
		FVector Fire(FVector startHitScanLoc);
	/// <summary>
	/// Blueprint-callable function that applies recoil to the players camera
	/// </summary>
	UFUNCTION(BlueprintCallable)
		void ApplyRecoil(ACharacter* playerCharacter, float recoilAngleYaw, float recoilAnglePitch);
};
