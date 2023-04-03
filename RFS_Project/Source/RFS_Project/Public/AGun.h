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
/* This is the base class for gun functionality regarding shooting & reloading*/
class RFS_PROJECT_API AAGun : public AActor
{
	GENERATED_BODY()
	
	/* Struct for containing the Actor and Location of Hit returned by the "Trace" function*/
	struct FTraceReturn
	{
		AActor* TraceActor;
		FVector HitLoc;
	};

public:	
	/* Called at the beginning of play to setup the AGun actor values*/
	void BeginPlay() override;
	/*
	* Called every tick on the actor
	* @param DeltaSeconds - Time since last frame
	*/
	void Tick(float DeltaSeconds) override;
	// Sets default values for this actor's properties
	AAGun();
	/*
	* Blueprint-callable function that tells the gun to fire
	* @param StartHitScanLoc - Starting point of the line trace for the gun to fire from
	* @return Returns the first point of impact for the line trace
	*/
	UFUNCTION(BlueprintCallable)
		FVector Fire(FVector StartHitScanLoc);
	/*
	* Blueprint-callable function that applies recoil to the players' camera
	* @param PlayerCharacter - Player to apply recoil to
	* @param RecoilAngleYaw - Size of recoil to apply on the yaw angle
	* @param RecoilAnglePitch - Size of recoil to apply on the pitch angle
	*/
	UFUNCTION(BlueprintCallable)
		void ApplyRecoil(ACharacter* PlayerCharacter, float RecoilAngleYaw, float RecoilAnglePitch);
	/*
	* Blueprint-callable function that sets whether the gun is firing
	* @param Value - The value to bIsGunFiring to
	*/
	UFUNCTION(BlueprintCallable)
		void SetIsGunFiring(bool Value);
	/*
	* Blueprint-callable function that returns whether the gun is firing
	* @return Returns the value of bIsGunFiring
	*/
	UFUNCTION(BlueprintCallable)
		bool IsGunFiring();
	/*
	* Blueprint-callable function that returns current ammo in the gun
	* @return Returns the value of CurrentAmmo
	*/
	UFUNCTION(BlueprintCallable)
		int GetCurrentAmmo();
	/* Blueprint-Implementable event that is called to update the GunStartHitScanLoc*/
	UFUNCTION(BlueprintImplementableEvent)
		void OnStartHitScanLocUpdate();
	/*Blueprint-callable function that plays the reload animation*/
	UFUNCTION(BlueprintCallable)
		void Reload();
	/*
	* Blueprint-callable function that returns whether the gun is being reloaded when empty of ammo
	* @return Returns whether reloading when empty of ammo
	*/
	UFUNCTION(BlueprintCallable)
		bool IsReloadingOnEmpty();
	/*
	* Blueprint-callable function that returns whether the gun is being reloaded when not empty of ammo
	* @return Returns whether reloading when not empty of ammo
	*/
	UFUNCTION(BlueprintCallable)
		bool IsReloadingOnHalfMag();
	/*
	* Blueprint-callable function for altering gun accuracy modifier
	* @param ValueToAlterBy - Value to add onto the gun accuracy modifier variable
	*/
	UFUNCTION(BlueprintCallable)
		void AlterGunAccuracyModifier(float ValueToAlterBy);
	/*
	* Blueprint-callable function for resetting the gun accuracy modifier
	*/
	UFUNCTION(BlueprintCallable)
		void ResetGunAccuracyModifier();
public:
	// EDITOR VARIABLES

	/*Value for base accuracy of the gun 0-1, higher the value higher the accuracy*/
	UPROPERTY(EditAnywhere)
		float GunAccuracy;
	UPROPERTY(EditAnywhere)
		float GunShotSpread;
	/*Value for the firerate of the gun 0-1, lower the value faster the firerate*/
	UPROPERTY(EditAnywhere)
		float GunFirerate;
	/*Name of the socket that the gun is attached to*/
	UPROPERTY(EditAnywhere)
		FName FireSocket;
	/*Value for the max ammo in the gun*/
	UPROPERTY(EditAnywhere)
		int MaxAmmo;
	/*Bool for whether the gun is equipped for the player*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayerGun;
	/*Value for the range of the guns' bullets*/
	UPROPERTY(EditAnywhere)
		float GunRange;
	/*Bool for whether the gun is set to automatic*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsGunAutomatic;
	// BLUEPRINT PROPERTIES
	/*Reference to the APlayableCharacter actor we are equipped to*/
	UPROPERTY(BlueprintReadWrite)
		APlayableCharacter* PawnEquippedTo;
	/*Vector position of the muzzle of the gun*/
	UPROPERTY(BlueprintReadWrite)
		FVector MuzzlePoint;
	/*Vector position to fire the line trace from for shooting*/
	UPROPERTY(BlueprintReadWrite)
		FVector GunStartHitScanLoc;
	/*Vector position for where the guns' last bullet hit*/
	UPROPERTY(BlueprintReadOnly)
		FVector GunLastHitLoc;
protected:
	/*
	* Calculates the accuracy of the shot
	* @return Returns a vector offset to the trajectory of the shot
	*/
	FVector CalculateAccuracy();

	/*
	* Completes a multi raycast for a component of the given type
	* @param StartTrace - Start point of the trace
	* @param EndTrace - End point of the trace
	* @return The first hit object whether it was object of the type or piece of enviornment
	*/
	template<typename T>
	FTraceReturn Trace(FVector StartTrace, FVector EndTrace);
	
	/*
	* Resets the CurrentAmmo to MaxAmmo 
	* @note Normally executes after a call to reload
	*/
	void ResetAmmo();
protected:
	/*Base offset for the trajectory*/
	FVector TrajectoryOffset = FVector(1.0f, 0.0f, 1.0f);
	/*Timer handle for the reload timer*/
	FTimerHandle ReloadTimer;
	/*Value for the time to wait for the reload timer*/
	float ReloadAnimWaitTime = 2.0f;
	/*Value for modifying the base gun accuracy*/
	float GunAccuracyModifier;
	/*Bool for whether the gun is firing*/
	bool bIsGunFiring = false;
	/*Value for the current count till we can fire*/
	float GunFireRateCounter;
	/*Value for the amount of ammo we have in the gun*/
	int CurrentAmmo = 0;
	/*Bool for whether or not we are reloading on empty*/
	bool bReloadingOnEmpty = false;
	/*Bool for whether or not we are reloading in a half mag*/
	bool bReloadingOnHalfMag = false;
};
