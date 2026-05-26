// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMS_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Data/TMS_InputData.h"
#include "GameFramework/SpringArmComponent.h"
#include "TMS_LS/TMS_LSCharacter.h"
#include "TMS_Player.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API ATMS_Player : public ATMS_BaseCharacter
{
	GENERATED_BODY()

	ATMS_Player();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inputs)
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inputs)
	TObjectPtr<UTMS_InputData> InputData;

private:
	FVector2D MoveInput;

	float TargetFOV = 90.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool CanSprint() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMoveInput(const FInputActionValue& Value);
	void OnLookInput(const FInputActionValue& Value);
	void OnSprintInput(const FInputActionValue& Value);
	void OnCrouchInput(const FInputActionValue& Value);
};
