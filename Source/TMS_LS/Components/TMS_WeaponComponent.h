// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TMS_LS/Items/Weapons/TMS_BaseWeapon.h"
#include "TMS_WeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TMS_LS_API UTMS_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTMS_WeaponComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATMS_BaseWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ATMS_BaseWeapon> CurrentWeapon;

protected:
	virtual void BeginPlay() override;

public:

	void SpawnWeapon();
};
