// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCharacter_Kostin.h"
#include "MotionWarpingComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TMS_LS/TMS_LSCharacter.h"
#include "TMS_LS/Core/Data/TMS_InputData.h"
#include "CPlayer_Kostin.generated.h"

class UTMS_WeaponComponent_Kostin;
class UTMS_HealthComponent_Kostin;

UCLASS()
class TMS_LS_API ACPlayer_Kostin : public ACCharacter_Kostin
{
	GENERATED_BODY()
	ACPlayer_Kostin();
	
private:
	FVector2D MoveInput;
	

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inputs)
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UMotionWarpingComponent> MotionWarper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inputs)
	TObjectPtr<UTMS_InputData> InputData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UTMS_WeaponComponent_Kostin> WeaponComponent_Kostin;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UTMS_HealthComponent_Kostin> HealthComponent_Kostin;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fall Damage")
	float FallDamageVelocity = 700.0f; 
	
	void OnMoveInput(const FInputActionValue& InputActionValue);
	void OnLookInput(const FInputActionValue& InputActionValue);
	void OnSprintInput(const FInputActionValue& InputActionValue);
	void UseItem(const FInputActionValue& InputActionValue);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;
	
	
	APlayerController* PlayerController;
};
