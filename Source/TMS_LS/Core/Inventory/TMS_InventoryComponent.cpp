// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_InventoryComponent.h"
#include "TMS_LS/Utilities/TMS_DeveloperSettings.h"

//#include "TMS_LS/Core/TMS_DataSettings.h"

// Sets default values for this component's properties
UTMS_InventoryComponent::UTMS_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTMS_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Slots.Init(FItemSlotData(), ContainerSize);
	OnInventoryInitialized.Broadcast();
}

void UTMS_InventoryComponent::AddItem(const FItemSlotData& InItem, bool& OutSuccess)
{
	int32 FoundId = 0;
	if (InItem.ItemID == NAME_None || InItem.Amount == 0)
	{
		OutSuccess = true;
		return;
	}
	if (HasNotFullSlotOfItem(InItem.ItemID, FoundId))
	{
		int32 Overflow = 0;
		if (TryToFill(FoundId, InItem, Overflow))
		{
			OutSuccess = true;
			OnInventoryUpdated.Broadcast();
			return;
		}
		AddItem(FItemSlotData(InItem.ItemID, Overflow), OutSuccess);
	}
	else
	{
		if (CreateNewEmptySlotOfType(InItem.ItemID))
		{
			AddItem(InItem, OutSuccess);
		}
		else
		{
			OutSuccess = false;
		}
	}
}

void UTMS_InventoryComponent::RemoveItem(FItemSlotData InItem)
{
	int32 OutId = 0;
	if (!FindFirstSlotOfType(OutId, InItem.ItemID)) return;

	FItemSlotData* FoundItem = &Slots[OutId];

	if (InItem.Amount >= FoundItem->Amount)
	{
		InItem.Amount-=FoundItem->Amount;
		FoundItem->ItemID = FName();
		FoundItem->Amount = 0;
		if (InItem.Amount == 0)
		{
			OnInventoryUpdated.Broadcast();
			return;
		};
		
		RemoveItem(InItem);
	}
	else
	{
		FoundItem->Amount-=InItem.Amount;
	}
	OnInventoryUpdated.Broadcast();
}

void UTMS_InventoryComponent::SwapItems(int32 InSlot, int32 OutSlot)
{
	if (Slots.Num()-1 < FMath::Max(OutSlot, InSlot)) return;	
	FItemSlotData Temp = Slots[OutSlot];
	Slots[OutSlot] = Slots[InSlot];
	Slots[InSlot] = Temp;
	OnInventoryUpdated.Broadcast();
}


void UTMS_InventoryComponent::DEBUG_PrintSlots()
{
	FString Result = "Slots are:\n";
	for (auto Slot : Slots)
	{
		Result.Append(FString::Printf(TEXT("----%s : %i \n"), *Slot.ItemID.ToString(), Slot.Amount));
	}
	Result.Append(TEXT("----\n\n"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, Result);
}

bool UTMS_InventoryComponent::IsEmpty()
{
	for (const auto& Item : Slots)
	{
		if (Item.ItemID != NAME_None) return false;
	}
	return true;
}

bool UTMS_InventoryComponent::HasNotFullSlotOfItem(const FName& ItemID, int32& OutIndex)
{
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		int32 MaxSlot = GetMaxAmount(ItemID);
		if (Slots[i].ItemID == ItemID && Slots[i].Amount < MaxSlot)
		{
			OutIndex = i;
			return true;
		}
	}
	OutIndex = -1;
	return false;
}

bool UTMS_InventoryComponent::FindFirstSlotOfType(int32& OutIndex, const FName InName)
{
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].ItemID == InName)
		{
			OutIndex = i;
			return true;
		}
	}
	OutIndex = -1;
	return false;
}

bool UTMS_InventoryComponent::CreateNewEmptySlotOfType(const FName& ItemID)
{
	int32 EmptySlot = -1;
	if (FindFirstSlotOfType(EmptySlot))
	{
		Slots[EmptySlot].ItemID = ItemID;
	}
	else
	{
		return false;
	}
	return true;
}

bool UTMS_InventoryComponent::TryToFill(int32 InID, const FItemSlotData& InItem, int32& Overflow)
{
	if (!Slots.IsValidIndex(InID)) return true;
	FItemSlotData* Item = &Slots[InID];
	int32 MaxSlot = GetMaxAmount(InItem.ItemID);

	if (Item->Amount + InItem.Amount > MaxSlot)
	{
		Overflow = (Item->Amount + InItem.Amount) - MaxSlot;
		Item->Amount = MaxSlot;
		return false;
	}
	Item->Amount += InItem.Amount;
	return true;
}

int32 UTMS_InventoryComponent::GetMaxAmount(FName ItemID)
{
	const UTMS_DeveloperSettings* Settings = GetDefault<UTMS_DeveloperSettings>();
	if (!IsValid(Settings) || !IsValid(Settings->ItemDataTable.LoadSynchronous())) return 0;
	
	FItemData* Item = Settings->ItemDataTable->FindRow<FItemData>(ItemID, "");
	if (!Item) return 0;
	
	return Item->MaxAmount;
}
