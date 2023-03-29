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
	
	struct TraceReturn
	{
		AActor* TraceActor;
		FVector HitLoc;
	};

public:	
	// Sets default values for this actor's properties
	AAGun();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
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
	UPROPERTY(EditAnywhere)
		int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayerGun;
	UPROPERTY(EditAnywhere)
		float GunRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsGunAutomatic;
	// BLUEPRINT PROPERTIES
	UPROPERTY(BlueprintReadWrite)
		APlayableCharacter* PawnEquippedTo;
	UPROPERTY(BlueprintReadWrite)
		FVector MuzzlePoint;
	UPROPERTY(BlueprintReadWrite)
		FVector GunStartHitScanLoc;
	UPROPERTY(BlueprintReadOnly)
		FVector GunLastHitLoc;
protected:
	FVector TrajectoryOffset = FVector(1.0f, 0.0f, 0.0f);
	FTimerHandle ReloadTimer;
	float ReloadAnimWaitTime = 2.0f;
	bool bIsGunFiring = false;
	float GunFireRateCounter;
	int CurrentAmmo = 0;
	bool bReloadingOnEmpty = false;
	bool bReloadingOnHalfMag = false;
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
	TraceReturn Trace(FVector StartTrace, FVector EndTrace);

	

	void ResetAmmo();
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
	UFUNCTION(BlueprintCallable)
		void SetIsGunFiring(bool Value);
	UFUNCTION(BlueprintCallable)
		bool IsGunFiring();
	UFUNCTION(BlueprintCallable)
		int GetCurrentAmmo();
	UFUNCTION(BlueprintImplementableEvent)
		void OnStartHitScanLocUpdate();
	/// <summary>
	/// Function called to reload the gun
	/// </summary>
	UFUNCTION(BlueprintCallable)
		void Reload();
	UFUNCTION(BlueprintCallable)
		bool IsReloadingOnEmpty();
	UFUNCTION(BlueprintCallable)
		bool IsReloadingOnHalfMag();
};
