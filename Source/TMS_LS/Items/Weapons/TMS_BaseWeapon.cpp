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
	if (bInActive)
	{
		GetWorldTimerManager().SetTimer(CooldownHandle,
			this, &ThisClass::Shoot, 1/Speed, true, 0.f);
	}
}

// Called when the game starts or when spawned
void ATMS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATMS_BaseWeapon::Shoot()
{
	if (!bIsActive)
	{
		GetWorldTimerManager().ClearTimer(CooldownHandle);
	}
	FHitResult Hit;

	ATMS_Player* Char = Cast<ATMS_Player>(GetOwner());
	if (!Char) return;

	FVector EndLocation = Char->Camera->GetComponentLocation();
	FVector Direction = Char->Camera->GetForwardVector();
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Char);
	IgnoreActors.Add(this);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActors(IgnoreActors);

	GetWorld()->LineTraceSingleByChannel(Hit,
		GetMuzzleLocation(), EndLocation + Direction * Distance,
		ECollisionChannel::ECC_Pawn, CollisionParams);
	DrawDebugLine(GetWorld(),GetMuzzleLocation(), EndLocation + Direction * Distance, FColor::Green, false, 0.5f, 0, 1.f);

	if (Hit.bBlockingHit && Hit.GetActor())
	{
		Hit.GetActor()->TakeDamage(Damage, FDamageEvent{}, Char->GetController(), Char);
	}
	
	ApplyRecoil();
}

void ATMS_BaseWeapon::ApplyRecoil()
{
	float RandX = FMath::FRandRange(-Recoil.X, Recoil.X);
	float RandY = FMath::FRandRange(-Recoil.Y, Recoil.Y);
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	Player->AddControllerYawInput(RandX);
	Player->AddControllerPitchInput(RandY);
}

FVector ATMS_BaseWeapon::GetMuzzleLocation()
{
	return WeaponMesh->GetSocketLocation(FName("S_Muzzle"));
}