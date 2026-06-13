// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/UW_Main_Kostin.h"
#include "HUD_Kostin.generated.h"

/**
 * 
 */

UCLASS()
class TMS_LS_API AHUD_Kostin : public AHUD
{
	GENERATED_BODY()
public:

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	
	void DrawCrosshair();
	
	void ToggleInventory();
	void TogglePauseMenu();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUW_Main_Kostin> MainWidgetClass;
	
private:
	UPROPERTY()
	UUW_Main_Kostin* MainWidget = nullptr;
	
};
