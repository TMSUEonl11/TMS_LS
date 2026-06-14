// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ItemSlot_Kostin.h"



void UUW_ItemSlot_Kostin::NativeConstruct()
{
	
	if (APlayerController* PC = GetOwningPlayer())
	{	
		PC->OnPossessedPawnChanged.AddDynamic(this, &UUW_ItemSlot_Kostin::OnPawnChanged);
		if (PC->GetPawn())OnPawnChanged(nullptr, PC->GetPawn());
	}
	Super::NativeConstruct();
}

void UUW_ItemSlot_Kostin::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                               UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
//	if (!InventoryComponent)return;
	
}

void UUW_ItemSlot_Kostin::OnPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (!NewPawn)return;
	InventoryComponent = NewPawn->GetComponentByClass<UInventoryComponent_Kostin>();
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Component FALSE ItemSlot"));
	}
	else UE_LOG(LogTemp, Error, TEXT("Inventory Component TRUE ItemSlot"));
	//if (InventoryComponent)
//	{
//		OnInventoryReady.Broadcast();
//	}
}