// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TMS_LS/Kostin/Item/InventoryComponent_Kostin.h"
#include "UW_Inventory_Kostin.generated.h"

/**
 * 
 */


UCLASS()
class TMS_LS_API UUW_Inventory_Kostin : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void InitData(TArray<FSlotData_Kostin>& Slots,int32 &ContainerSize);
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateData();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "HUD")
	UInventoryComponent_Kostin * InventoryComponent;
	};
