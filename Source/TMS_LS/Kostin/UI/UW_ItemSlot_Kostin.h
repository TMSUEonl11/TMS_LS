// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TMS_LS/Kostin/Item/InventoryComponent_Kostin.h"
#include "UW_ItemSlot_Kostin.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API UUW_ItemSlot_Kostin : public UUserWidget
{
	GENERATED_BODY()
	UFUNCTION()
	void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	UInventoryComponent_Kostin * InventoryComponent;
};
