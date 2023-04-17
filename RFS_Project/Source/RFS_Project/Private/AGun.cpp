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
	// Reset gun properties
	GunFireRateCounter = GunFirerate;
	CurrentAmmo = MaxAmmo;
}

void AAGun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Are we firing on automatic?
	if (bIsGunAutomatic)
	{
		// Are we firing & has enough time passed to shoot again
		if (GunFireRateCounter >= GunFirerate && bIsGunFiring == true)
		{
			// Do we have some ammo?
			if (CurrentAmmo > 0)
			{
				// Let our shooter know we are firing
				PawnEquippedTo->OnGunFire();
				// Update the GunStartHitScanLoc
				OnStartHitScanLocUpdate();
				GunLastHitLoc = Fire(GunStartHitScanLoc);
				CurrentAmmo -= 1;
				GunFireRateCounter = 0;
			}
			else
			{
				// Check we aren't already reloading before calling Reload()
				if (!bReloadingOnHalfMag && !bReloadingOnEmpty)
				{
					Reload();
				}
				// Let our shooter know we are trying to fire on empty
				PawnEquippedTo->OnGunFire();
			}
		}
		GunFireRateCounter += DeltaSeconds;
	}

}

FVector AAGun::Fire(FVector StartHitScanLoc)
{
	// Can't fire yet
	if (GunFireRateCounter < GunFirerate)
	{
		return FVector();
	}
	FVector AccOffset = CalculateAccuracy();
	FRotator Rotation;
	FVector LineVector;
	// Is this gun equipped to the player?
	if (bPlayerGun)
	{
		Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
		LineVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * GunRange;
	}
	else
	{
		Rotation = GetActorRightVector().Rotation();
		LineVector = GetActorRightVector() * GunRange;
	}
	// Fire a line trace
	FTraceReturn returnedTrace = Trace<IHealth>(StartHitScanLoc, (StartHitScanLoc + LineVector) + (AccOffset) * 20);
	AActor* HitActor = returnedTrace.TraceActor;
	// Did we actually hit anything?
	if (HitActor)
	{
		if (APlayableCharacter* character = Cast<APlayableCharacter>(HitActor))
		{
			// Did what we hit have health?
			IHealth* HealthObj = Cast<IHealth>(character);
			if (HealthObj)
			{
				//TODO remove this in favor of having a damage variable on the gun
				if (bPlayerGun)
				{
					HealthObj->OnDamage(1.0f, PawnEquippedTo);
				}
				else
				{
					HealthObj->OnDamage(10.0f, PawnEquippedTo);
				}
			}
		}
		else
		{
			// Return our hit point location
			return returnedTrace.HitLoc;
		}
	}
	return FVector();
	
}

template<typename T>
AAGun::FTraceReturn AAGun::Trace(FVector StartTrace, FVector EndTrace)
{
	TArray<FHitResult> OutHit;
	FTraceReturn TraceToReturn;
	TraceToReturn.TraceActor = nullptr;
	TraceToReturn.HitLoc = FVector();
	// Ask Unreal to perform a line trace
	GetWorld()->LineTraceMultiByChannel(OutHit, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility);
	// DEBUG PURPOSES 
	if (!bPlayerGun)
	{
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.0f);
	}
	// Actor pointer for if we don't hit the enemy but instead want to record hitting the enviornment
	AActor* EnviornmentHit = nullptr;
	for (int i = 0; i < OutHit.Num(); i++)
	{
		AActor* HitActor = OutHit[i].GetActor();
		if (HitActor)
		{
			// Cast to determine if the actor hit is of the given type
			APlayableCharacter* character = Cast<APlayableCharacter>(OutHit[i].GetActor());
			IHealth* HealthObj = Cast<IHealth>(character);
			// If the object is of the given type and we have not hit ourselves
			if (HealthObj && HitActor != PawnEquippedTo)
			{
				TraceToReturn.TraceActor = HitActor;
				TraceToReturn.HitLoc = OutHit[i].ImpactPoint;
				return TraceToReturn;
			}
			else if(HitActor != PawnEquippedTo && EnviornmentHit == nullptr)
			{
				EnviornmentHit = OutHit[i].GetActor();
				TraceToReturn.TraceActor = EnviornmentHit;
				TraceToReturn.HitLoc = OutHit[i].ImpactPoint;
			}
		}
	}
	return TraceToReturn;
}

void AAGun::Reload()
{
	// Decide whether we are reloading on empty or a half full mag
	if (CurrentAmmo > 0)
	{
		bReloadingOnHalfMag = true;
	}
	else
	{
		bReloadingOnEmpty = true;
	}
	// Play the reload animation
	PawnEquippedTo->PlayReloadAnimation();
	// Set the timer to execute the ammo reset once the animation has finished
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AAGun::ResetAmmo, ReloadAnimWaitTime, false);
}

void AAGun::ResetAmmo()
{
	CurrentAmmo = MaxAmmo;
	bReloadingOnEmpty = false;
	bReloadingOnHalfMag = false;
}

void AAGun::ApplyRecoil(ACharacter* PlayerCharacter, float RecoilAngleYaw, float RecoilAnglePitch)
{
	PlayerCharacter->AddControllerYawInput(RecoilAngleYaw);
	PlayerCharacter->AddControllerPitchInput(RecoilAnglePitch);
}

FVector AAGun::CalculateAccuracy()
{
	//// Grab a random number between 0 and 3
	int Random = rand() % 4;	

	// First add modifier to base accuracy
	float CalculatedGunAccuracy = GunAccuracy + GunAccuracyModifier;
	// Invert
	CalculatedGunAccuracy = 1 - CalculatedGunAccuracy;
	// Check for out of bounds accuracy
	if (CalculatedGunAccuracy < 0)
	{
		CalculatedGunAccuracy = 0.0f;
	}

	// GunShotSpread -> 10 CalculatedGunAccuracy -> 0.1 then 10 * 0.1 = 1 (highly accuracte)
	int ShotSpreadRange = static_cast<int>(GunShotSpread * CalculatedGunAccuracy);
	int Offset;
	if (ShotSpreadRange != 0)
	{
		Offset = rand() % ShotSpreadRange;
	}
	else
	{
		Offset = 0;
	}

	if (Random < 2)
	{
		return TrajectoryOffset * Offset;
	}
	else
	{
		return TrajectoryOffset * -Offset;
	}
}

void AAGun::AlterGunAccuracyModifier(float ValueToAlterBy)
{
	GunAccuracyModifier += ValueToAlterBy;
	if (GunAccuracyModifier > 1)
	{
		GunAccuracyModifier = 1.0f;
	}
	else if (GunAccuracyModifier < -1)
	{
		GunAccuracyModifier = -1.0f;
	}
}

void AAGun::ResetGunAccuracyModifier()
{
	GunAccuracyModifier = 0.0f;
}

void AAGun::SetIsGunFiring(bool Value)
{
	bIsGunFiring = Value;
	// If we have just stopped firing reset the counter so there isn't a delay when we shoot next
	if (bIsGunFiring == false)
	{
		GunFireRateCounter = GunFirerate;
		PawnEquippedTo->OnGunFiringStopped();
	}
}

bool AAGun::IsGunFiring()
{
	return bIsGunFiring;
}

int AAGun::GetCurrentAmmo()
{
	return CurrentAmmo;
}

bool AAGun::IsReloadingOnEmpty()
{
	return bReloadingOnEmpty;
}

bool AAGun::IsReloadingOnHalfMag()
{
	return bReloadingOnHalfMag;
}