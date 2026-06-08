// Fill out your copyright notice in the Description page of Project Settings.

#include "TMS_WeaponComponent_Kostin.h"

#include "TMS_LS/Core/TMS_Player.h"
#include "TMS_LS/Kostin/Weapons/TMS_BaseWeapon_Kostin.h"

UTMS_WeaponComponent_Kostin::UTMS_WeaponComponent_Kostin()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTMS_WeaponComponent_Kostin::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UTMS_WeaponComponent_Kostin::SpawnWeapon()
{
	if (!GetWorld() || !GetOwner() || !WeaponClass) return;

	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	
	if (ATMS_BaseWeapon_Kostin* NewWeapon = GetWorld()->SpawnActor<ATMS_BaseWeapon_Kostin>(WeaponClass))
	{
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentWeapon->WeaponMesh->SetSimulatePhysics(true);
			CurrentWeapon = nullptr;
		}
		
		CurrentWeapon = NewWeapon;
		CurrentWeapon->SetOwner(GetOwner());
		CurrentWeapon->AttachToComponent(Player->GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentWeapon->DesiredSocket);

		if (CurrentWeapon->AnimLayer)
		{
			Player->GetMesh()->GetAnimInstance()->LinkAnimClassLayers(NewWeapon->AnimLayer);
		}
		
	}
	
}

