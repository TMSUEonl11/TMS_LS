// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TMS_InventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TMS_LS_API UTMS_InventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	bool AddItemToController(APlayerController* Target, FItemSlotData Item);

	UFUNCTION(BlueprintCallable)
	bool AddItem(AActor* Target, FItemSlotData Item);
		
	UFUNCTION(BlueprintCallable)
	void GetItemData(FName ItemID, FItemData& OutItem);
};
