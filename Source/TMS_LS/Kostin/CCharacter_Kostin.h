// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TMS_LS/Core/Data/TMS_DataTypes.h"
#include "CCharacter_Kostin.generated.h"

UCLASS()
class TMS_LS_API ACCharacter_Kostin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter_Kostin();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	FTMS_AnimData VaultAnims;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSprinting = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator CurrentRotation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
