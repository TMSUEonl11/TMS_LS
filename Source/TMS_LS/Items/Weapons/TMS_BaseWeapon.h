// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMS_BaseWeapon.generated.h"

UCLASS()
class TMS_LS_API ATMS_BaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMS_BaseWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
	TSubclassOf<UAnimInstance> AnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|State")
	bool bIsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
	float Speed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
	float Distance = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
	FName DesiredSocket = "S_Weapon_R";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Data")
	FVector2D Recoil = FVector2D::ZeroVector;

	FTimerHandle CooldownHandle;

	void Fire_Input(bool bInActive);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Shoot();

	void ApplyRecoil();

	FVector GetMuzzleLocation();
};
