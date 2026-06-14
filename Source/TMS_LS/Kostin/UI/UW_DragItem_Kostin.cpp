// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_DragItem_Kostin.h"

void UUW_DragItem_Kostin::NativeConstruct()
{
	UGameInstance* GameInstance = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
	if (GameInstance)
	{
		IS = GameInstance->GetSubsystem<UGameInstanceSubsystem_Kostin>();	
		if (!IS) return;	
	}
	Super::NativeConstruct();
}

bool UUW_DragItem_Kostin::InitData(int32 ItemID, FItemData_Kostin &ItemData)
{
	if (!IS) return false;
	return IS->GetItemDataByID(ItemID,ItemData);
}
