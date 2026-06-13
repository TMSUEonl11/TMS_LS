// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure.h"
#include "UW_Inventory_Kostin.h"
#include "Blueprint/UserWidget.h"
#include "TMS_LS/Kostin/Item/InventoryComponent_Kostin.h"
#include "UW_Main_Kostin.generated.h"
/**
 * 
 */
class AHUD_Kostin;
UCLASS()
class TMS_LS_API UUW_Main_Kostin : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeWidget();
	
	
	UFUNCTION(BlueprintCallable)
	void SetWindowMode(EUIState_Kostin NewMode);
	
	EUIState_Kostin GetCurrentMode() const { return CurrentMode; }
	
	void HideAllMenus();	
	//FOnInputModeChanged OnInputModeChanged;
	
protected:
//	UFUNCTION()
//	void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override; 
	//UPROPERTY(meta = (BindWidget))
	//UCrosshairWidget* CrosshairPanel;

	UPROPERTY(meta = (BindWidget))
	UUW_Inventory_Kostin* InventoryPanel;

	//UPROPERTY(meta = (BindWidget))
	//UPauseMenuWidget* PauseMenuPanel;


private:
	EUIState_Kostin CurrentMode = EUIState_Kostin::EUIS_Game;
	void UpdateInputMode();
	
//	APlayerController* GetOwningPC() const;
	UPROPERTY()
	AHUD_Kostin *HUD= nullptr;
	//UInventoryComponent_Kostin * InventoryComponent;
	
};
