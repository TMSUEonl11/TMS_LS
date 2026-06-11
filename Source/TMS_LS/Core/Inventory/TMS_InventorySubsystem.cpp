// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_InventorySubsystem.h"

#include "TMS_InventoryComponent.h"

bool UTMS_InventorySubsystem::AddItem(APlayerController* Target, FItemSlotData Item)
{
	if (!Target || !Target->GetPawn()) return false;
	UTMS_InventoryComponent* IC = Target->GetPawn()->GetComponentByClass<UTMS_InventoryComponent>();
	if (!IC) return false;
	bool Result = false;
	IC->AddItem(Item, Result);
	return Result;
}
