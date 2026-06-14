// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TMS_LS/Kostin/Utilities/GameInstanceSubsystem_Kostin.h"
#include "UW_DragItem_Kostin.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API UUW_DragItem_Kostin : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override; 
	
	public:
	UFUNCTION(BlueprintCallable, Category="Data")
	bool InitData(int32 ItemID, FItemData_Kostin &ItemData);
	
	UPROPERTY()
	UGameInstanceSubsystem_Kostin* IS;

};
