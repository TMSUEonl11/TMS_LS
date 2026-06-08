// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TMS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API ATMS_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

private:
	void DrawCrosshair();
};
