// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TMS_AbilitySystemComponent.h"
#include "AbilitySystem/TMS_AttributeSet.h"
#include "Data/TMS_MovementData.h"
#include "GameFramework/Character.h"
#include "TMS_BaseCharacter.generated.h"

UCLASS()
class TMS_LS_API ATMS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATMS_BaseCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	TObjectPtr<UTMS_AbilitySystemComponent> AbilityComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	TObjectPtr<UTMS_AttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement)
	TObjectPtr<UTMS_MovementData> MovementData;

	virtual bool CanSprint()
	{
		if (!IsValid(MovementData)) return false;
		return true;
	}
	virtual bool CanCrouch() { return true; }
};
