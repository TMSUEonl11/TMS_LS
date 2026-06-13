// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Inventory_Kostin.h"



void UUW_Inventory_Kostin::NativeConstruct()
{
	Super::NativeConstruct();
	if (APlayerController* PC = GetOwningPlayer())
	{	
		PC->OnPossessedPawnChanged.AddDynamic(this, &UUW_Inventory_Kostin::OnPawnChanged);
		if (PC->GetPawn())OnPawnChanged(nullptr, PC->GetPawn());
	}
}

void UUW_Inventory_Kostin::OnPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (!NewPawn)return;
	InventoryComponent = NewPawn->GetComponentByClass<UInventoryComponent_Kostin>();
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Component FALSE"));
	}
	else UE_LOG(LogTemp, Error, TEXT("Inventory Component TRUE"));
	if (InventoryComponent)
	{
		OnInventoryReady.Broadcast();
	}
}

void UUW_Inventory_Kostin::InitData(TArray<FSlotData_Kostin>& Slots,int32 &ContainerSize)
{
	UE_LOG(LogTemp, Error, TEXT("Inventory Component"));
	if (!InventoryComponent)return;
	Slots=InventoryComponent->Slots;
	ContainerSize=InventoryComponent->ContainerSize;

}

void UUW_Inventory_Kostin::UpdateData()
{
	
}
