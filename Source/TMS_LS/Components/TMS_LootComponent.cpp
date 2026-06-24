// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_LootComponent.h"
#include "TMS_LS/Core/Inventory/TMS_InventorySubsystem.h"
#include "TMS_LS/Utilities/TMS_DeveloperSettings.h"


UTMS_LootComponent::UTMS_LootComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTMS_LootComponent::BeginPlay()
{
	Super::BeginPlay();
	GenerateLoot();
}

void UTMS_LootComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	for (auto& Loot : PossibleLoot)
	{
		Loot.DataTable = UTMS_DeveloperSettings::Get()->ItemDataTable.Get();
	}
}

void UTMS_LootComponent::GenerateLoot()
{
	if (!GetOwner()) return;
	for (int32 i = 0; i < LootItemsAmount; ++i)
	{
		int32 RandID = FMath::RandRange(0, PossibleLoot.Num() - 1);
		bool bSuccess = false;
		FItemSlotData ItemData;
		ItemData.Amount = 1;
		ItemData.ItemID = PossibleLoot[RandID].RowName;
		if (UTMS_InventorySubsystem* IS = GetWorld()->GetGameInstance()->GetSubsystem<UTMS_InventorySubsystem>())
		{
			IS->AddItem(GetOwner(), ItemData);
		}
	}
}

