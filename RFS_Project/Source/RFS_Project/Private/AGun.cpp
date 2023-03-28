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
	GunFireRateCounter = GunFirerate;
	CurrentAmmo = MaxAmmo;
}

void AAGun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//TODO try and reduce the if-statements
	if (bIsGunAutomatic)
	{
		if (GunFireRateCounter >= GunFirerate && bIsGunFiring == true)
		{
			if (CurrentAmmo > 0)
			{
				OnStartHitScanLocUpdate();
				Fire(GunStartHitScanLoc);
				CurrentAmmo -= 1;
				GunFireRateCounter = 0;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Attempting to reload");
				if (!bReloadingOnHalfMag && !bReloadingOnEmpty)
				{
					Reload();
				}
			}
		}
		GunFireRateCounter += DeltaSeconds;
	}
	
}

FVector AAGun::Fire(FVector StartHitScanLoc)
{
	FVector AccOffset = CalculateAccuracy();
	FRotator Rotation;
	if (bPlayerGun)
	{
		Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	}
	else
	{
		Rotation = GetActorRightVector().Rotation();
	}
	FVector LineVector;
	if (bPlayerGun)
	{
		LineVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * GunRange;
	}
	else
	{
		LineVector = GetActorRightVector() * GunRange;
	}
	AActor* HitActor = Trace<IHealth>(StartHitScanLoc, (StartHitScanLoc + LineVector) + (AccOffset) * 20);
	if (HitActor)
	{
		IHealth* HealthObj = dynamic_cast<IHealth*>(Cast<APlayableCharacter>(HitActor));
		if (HealthObj != nullptr)
		{
			if (bPlayerGun)
			{
				HealthObj->OnDamage(1.0f, PawnEquippedTo);
			}
			else
			{
				HealthObj->OnDamage(10.0f, PawnEquippedTo);
			}
		}
		else
		{
			return HitActor->GetActorLocation();
		}
	}
	return FVector();
	
}

template<typename T>
AActor* AAGun::Trace(FVector StartTrace, FVector EndTrace)
{
	TArray<FHitResult> OutHit;
	GetWorld()->LineTraceMultiByChannel(OutHit, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility);
	if (!bPlayerGun)
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.0f);
	}
	// Actor pointer for if we don't hit the enemy but instead want to record hitting the enviornment
	AActor* EnviornmentHit = nullptr;
	for (int i = 0; i < OutHit.Num(); i++)
	{
		AActor* HitActor = OutHit[i].GetActor();
		if (HitActor)
		{
			// Cast to determine if the actor hit is of the given type
			T* HealthObj = dynamic_cast<T*>(Cast<APlayableCharacter>(OutHit[i].GetActor()));
			// If the object is of the given type and we have not hit ourselves
			if (HealthObj && HitActor != PawnEquippedTo)
			{
				return HitActor;
			}
			else if(HitActor != PawnEquippedTo && EnviornmentHit == nullptr)
			{
				EnviornmentHit = OutHit[i].GetActor();
			}
		}
	}
	return EnviornmentHit;
}

void AAGun::Reload()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, "Reloading");
	if (CurrentAmmo > 0)
		bReloadingOnHalfMag = true;
	else
		bReloadingOnEmpty = true;
	PawnEquippedTo->PlayReloadAnimation();
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AAGun::ResetAmmo, ReloadAnimWaitTime, false);
}

void AAGun::ResetAmmo()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Resetting Ammo");
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
	int Random = rand() % 4;
	int ConvertedAccuracy = 1 - GunAccuracy;
	int OffsetScale = 10, MaximumVelocityOffset = 300;
	int CurrentVelocity = PawnEquippedTo->GetVelocity().Length();
	
	int MovingOffset;
	int VelocityPercentage = (CurrentVelocity / MaximumVelocityOffset);
	if (VelocityPercentage == 0)
	{
		MovingOffset = 0;
	}
	else
	{
		MovingOffset = 2 - (2 / VelocityPercentage) / 10;
	}
	int CalculatedOffset = rand() % (OffsetScale - (int)((GunAccuracy - MovingOffset) * OffsetScale));
	if (Random < 2)
	{
		return TrajectoryOffset * -CalculatedOffset;
	}
	else
	{
		return TrajectoryOffset * CalculatedOffset;
	}
}

void AAGun::SetIsGunFiring(bool Value)
{
	bIsGunFiring = Value;
	// If we have just stopped firing reset the counter so there isn't a delay when we shoot next
	if (bIsGunFiring == false)
	{
		GunFireRateCounter = GunFirerate;
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