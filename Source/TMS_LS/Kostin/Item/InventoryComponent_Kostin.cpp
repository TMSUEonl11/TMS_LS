// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent_Kostin.h"
#include "ItemData_Kostin.h"


// Sets default values for this component's properties
UInventoryComponent_Kostin::UInventoryComponent_Kostin()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent_Kostin::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* GameInstance = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
	if (GameInstance)
	{
		IS = GameInstance->GetSubsystem<UGameInstanceSubsystem_Kostin>();	
		if (!IS) return;	
	}
	
	Slots.Init(FSlotData_Kostin(), ContainerSize);
	for (int32 i = 0; i < ContainerSize; ++i)
	{
		Slots[i].SlotID = i;
	}
	Slots[0].ItemSlotData.ItemID =0;
	Slots[0].ItemSlotData.Amount =3;
	OnInventoryInitialized.Broadcast();
}







// Called every frame
void UInventoryComponent_Kostin::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UInventoryComponent_Kostin::GetMaxAmount(int32 ItemID)
{
	FItemData_Kostin ItemData;
	if (IS->GetItemDataByID(ItemID,ItemData))return ItemData.MaxAmount;
	return 0;
}

int32 UInventoryComponent_Kostin::AddItem(int32 ItemID, int32 Amount)
{
	if (Amount <= 0) return 0;
	int32 MaxAmount=GetMaxAmount(ItemID);
	if (MaxAmount <= 0) return Amount;
	int32 BufAmount=Amount;
	for (int32 i = 0; i < ContainerSize; ++i)
	{
		if (Slots[i].ItemSlotData.ItemID != ItemID) continue;
		if (Slots[i].ItemSlotData.Amount >= MaxAmount) continue;
		if (Slots[i].ItemSlotData.Amount + BufAmount <= MaxAmount)
		{
			Slots[i].ItemSlotData.Amount += BufAmount;
			OnInventoryUpdated.Broadcast();
			return 0;
		}
		else
		{
			BufAmount=BufAmount-(MaxAmount-Slots[i].ItemSlotData.Amount);
			Slots[i].ItemSlotData.Amount=MaxAmount;
			if (BufAmount)continue;
			OnInventoryUpdated.Broadcast();
			return 0;
		}
	}
	for (int32 i = 0; i < ContainerSize; ++i)
	{
		if (Slots[i].ItemSlotData.ItemID!=-1)continue;
		Slots[i].ItemSlotData.ItemID = ItemID;
		if (BufAmount < MaxAmount)
		{
			Slots[i].ItemSlotData.Amount = BufAmount;
			OnInventoryUpdated.Broadcast();
			return 0;
		}
		else
		{
			Slots[i].ItemSlotData.Amount = MaxAmount;
			BufAmount-=MaxAmount;
			continue;
		}


	}
	OnInventoryUpdated.Broadcast();
	return BufAmount;
}

