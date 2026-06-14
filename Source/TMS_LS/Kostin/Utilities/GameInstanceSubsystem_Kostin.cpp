// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceSubsystem_Kostin.h"
#include "DeveloperSettings_Kostin.h"
#include "TMS_LS/Kostin/Item/InventoryComponent_Kostin.h"


void UGameInstanceSubsystem_Kostin::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	const UDeveloperSettings_Kostin* Settings = UDeveloperSettings_Kostin::Get();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("Не удалось получить UGameInstanceSubsystem_Kostin"));
		return;
	}
	 else UE_LOG(LogTemp, Warning, TEXT("Получили UGameInstanceSubsystem_Kostin"));
	 TSoftObjectPtr<UDataTable> SoftTablePtr = Settings->ItemDataTable_Kostin;
	 ItemDataTable = SoftTablePtr.LoadSynchronous();
	 if (!ItemDataTable)
	 {
		UE_LOG(LogTemp, Error, TEXT("Не удалось загрузить DataTable из настроек (убедитесь, что свойство ItemDataTable заполнено в Project Settings)"));
	 }
	
}

bool UGameInstanceSubsystem_Kostin::GetItemDataByID(int32 ItemID, FItemData_Kostin& OutItemData)
{
	if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Не удалось получить ItemDataTable"));
		return false;
	}
	FName RowName = FName(*FString::FromInt(ItemID));
	FItemData_Kostin* RowData = ItemDataTable->FindRow<FItemData_Kostin>(RowName, TEXT(""));
	if (RowData)
	{
		OutItemData = *RowData;
		return true;
	}
	
return true;
}

int32 UGameInstanceSubsystem_Kostin::AddItem(APlayerController* Target, int32 ItemID, int32 Amount)
{
	if (!Target || !Target->GetPawn()) return Amount;
	UInventoryComponent_Kostin *IC =Target->GetPawn()->GetComponentByClass<UInventoryComponent_Kostin>();
	if (!IC) return Amount;
	
	return IC->AddItem(ItemID, Amount);
}
