// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TMS_LS/Kostin/Item/ItemData_Kostin.h"
#include "GameInstanceSubsystem_Kostin.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API UGameInstanceSubsystem_Kostin : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "ItemData")
	bool GetItemDataByID(int32 ItemID, FItemData_Kostin& OutItemData);

	UFUNCTION(BlueprintCallable)
	bool AddItem(APlayerController* Target, int32 ItemID, int32 Amount);
private:
	UPROPERTY()
	UDataTable* ItemDataTable;
};
