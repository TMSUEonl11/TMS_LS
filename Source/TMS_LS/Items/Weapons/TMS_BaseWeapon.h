// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMS_LS/Core/Data/TMS_DataTypes.h"
#include "TMS_BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoUpdateSignature, int32, NewAmmo);

UCLASS()
class TMS_LS_API ATMS_BaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMS_BaseWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	TSubclassOf<UAnimInstance> AnimLayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|State")
	bool bIsActive = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	int32 MaxAmmo = 30;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float Speed = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float Damage = 10.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float AimingFOV = 70.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float FOV_InterpSpeed = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	float Distance = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	FName DesiredSocket = "S_Weapon_R";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	FVector2D Recoil = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	FVector2D AimRecoil = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	FVector2D AccuracyAngle = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Data")
	FVector2D AimAccuracyAngle = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponAnimData ReloadAnims;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentAmmo = 0;

	UPROPERTY(BlueprintAssignable)
	FOnAmmoUpdateSignature OnAmmoUpdate;
		
	FTimerHandle CooldownHandle;
	
	bool bAiming;

	void Fire_Input(bool bInActive);

	void Aim_Input(bool bInActive);

	void Reload_Input();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Shoot();

	void ApplyRecoil();

	void SetAmmo(int32 InAmmo);
	
	void OnAnimNotify(EWeaponActionType WeaponAction);
	virtual void Reload();

	FVector GetMuzzleLocation();

	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutviewDirection);

	UFUNCTION()
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);

	APlayerController* GetPlayerController() const;

	
};
