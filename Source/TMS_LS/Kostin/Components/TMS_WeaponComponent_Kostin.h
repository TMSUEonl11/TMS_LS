// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TMS_LS/Kostin/Weapons/TMS_BaseWeapon_Kostin.h"
#include "TMS_WeaponComponent_Kostin.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TMS_LS_API UTMS_WeaponComponent_Kostin : public UActorComponent
{
	GENERATED_BODY()

public:
	UTMS_WeaponComponent_Kostin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATMS_BaseWeapon_Kostin> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ATMS_BaseWeapon_Kostin> CurrentWeapon;

protected:
	virtual void BeginPlay() override;

public:

	void SpawnWeapon();
};
