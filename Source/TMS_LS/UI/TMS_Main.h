// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMS_AttributePanel.h"
#include "Blueprint/UserWidget.h"
#include "TMS_LS/Core/TMS_HUD.h"
#include "TMS_Main.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API UTMS_Main : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTMS_AttributePanel> AttributePanel;

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUIStateChanged(EUIState InNewState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUIState CurrentUIState;
	
};
