// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_BaseWeapon.h"
#include "Engine/DamageEvents.h"
#include "Components/SkeletalMeshComponent.h"
#include "TMS_LS/Core/TMS_Player.h"


// Sets default values
ATMS_BaseWeapon::ATMS_BaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ATMS_BaseWeapon::Fire_Input(bool bInActive)
{
	bIsActive = bInActive;
	if (bInActive && !GetWorldTimerManager().IsTimerActive(CooldownHandle))
	{
		Shoot();
	}
} 

void ATMS_BaseWeapon::Aim_Input(bool bInActive)
{
	bAiming = bInActive;
}

void ATMS_BaseWeapon::Reload_Input()
{
	Fire_Input(false);
	Aim_Input(false);
	Reload();
}

// Called when the game starts or when spawned
void ATMS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
}

void ATMS_BaseWeapon::Shoot()
{
	if (!bIsActive)
	{
		GetWorldTimerManager().ClearTimer(CooldownHandle);
		return;
	}

	if (CurrentAmmo == 0)
	{
		Reload_Input();
		return;
	}
	
	FHitResult Hit;

	ATMS_Player* Char = Cast<ATMS_Player>(GetOwner());
	if (!Char) return;

	FVector StartLocation;
	FVector EndLocation;

	if (!GetTraceData(StartLocation, EndLocation)) return;

	SetAmmo(CurrentAmmo-1);
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Char);
	IgnoreActors.Add(this);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActors(IgnoreActors);

	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation,
		ECC_Camera, CollisionParams);

	if (Hit.bBlockingHit)
	{
		EndLocation = Hit.Location;
	}

	GetWorld()->LineTraceSingleByChannel(Hit,
		GetMuzzleLocation(), EndLocation,
		ECollisionChannel::ECC_Pawn, CollisionParams);
	DrawDebugLine(GetWorld(),GetMuzzleLocation(), EndLocation, FColor::Green, false, 0.5f, 0, 1.f);

	if (Hit.bBlockingHit && Hit.GetActor())
	{
		Hit.GetActor()->TakeDamage(Damage, FDamageEvent{}, Char->GetController(), Char);
	}
	
	ApplyRecoil();

	GetWorldTimerManager().SetTimer(CooldownHandle,
			this, &ThisClass::Shoot, 1/Speed);
	
}

void ATMS_BaseWeapon::ApplyRecoil()
{
	FVector2D TarRec = bAiming ? AimRecoil : Recoil;
	float RandX = FMath::DegreesToRadians(FMath::FRandRange(-TarRec.X, TarRec.X));
	float RandY = FMath::DegreesToRadians(FMath::FRandRange(-TarRec.Y, TarRec.Y));
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	Player->AddControllerYawInput(RandX);
	Player->AddControllerPitchInput(RandY);
}

void ATMS_BaseWeapon::SetAmmo(int32 InAmmo)
{
	CurrentAmmo = FMath::Clamp(InAmmo, 0, MaxAmmo);
	OnAmmoUpdate.Broadcast(CurrentAmmo);
}

void ATMS_BaseWeapon::OnAnimNotify(EWeaponActionType WeaponAction)
{
	switch (WeaponAction)
	{
	case EWeaponActionType::EWAT_Main:
		break;
	case EWeaponActionType::EWAT_Secondary:
		break;
	case EWeaponActionType::EWAT_Reload:
		SetAmmo(MaxAmmo);
		break;
	case EWeaponActionType::EWAT_MAX:
		break;
	}
}

void ATMS_BaseWeapon::Reload()
{
	if (CurrentAmmo == MaxAmmo) return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;

	if (!ReloadAnims.CAnim) return;
	float Length = Player->PlayAnimMontage(ReloadAnims.CAnim);
	if (UAnimInstance* WeaponAnim = WeaponMesh->GetAnimInstance())
	{
		WeaponAnim->Montage_Play(ReloadAnims.WAnim);
	}
	else
	{
		FTimerDelegate ReloadDelegate;
		ReloadDelegate.BindUObject(this, &ThisClass::OnAnimNotify, EWeaponActionType::EWAT_Reload);
		FTimerHandle ReloadHandle;
		GetWorldTimerManager().SetTimer(ReloadHandle,ReloadDelegate,
			Length * 0.8, false);
	}
	
}

FVector ATMS_BaseWeapon::GetMuzzleLocation()
{
	return WeaponMesh->GetSocketLocation(FName("S_Muzzle"));
}

bool ATMS_BaseWeapon::GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutviewDirection)
{
	const APlayerController* PC = GetPlayerController();
	if (!PC) return false;

	PC->GetPlayerViewPoint(OutViewLocation, OutviewDirection);
	return true;
}

bool ATMS_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FRotator ViewDirection;
	FVector ViewLocation;

	if (!GetPlayerViewPoint(ViewLocation, ViewDirection)) return false;

	TraceStart = ViewLocation;

	float RadX = FMath::DegreesToRadians(bAiming ? AimAccuracyAngle.X : AccuracyAngle.X);
	float RadY = FMath::DegreesToRadians(bAiming ? AimAccuracyAngle.Y : AccuracyAngle.Y);
	
	FVector TraceDirection = FMath::VRandCone(ViewDirection.Vector(),RadX/2, RadY/2);
	TraceEnd = TraceStart + TraceDirection * Distance;
	return true;
}

APlayerController* ATMS_BaseWeapon::GetPlayerController() const
{
	const ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}
