// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Main_Kostin.h"

#include "Channels/MovieSceneChannelTraits.h"
#include "TMS_LS/Core/Inventory/TMS_InventoryComponent.h"
#include "TMS_LS/Kostin/HUD_Kostin.h"

void UUW_Main_Kostin::InitializeWidget()
{
	//SetWindowMode(EWindowMode::Game);
}

void UUW_Main_Kostin::SetWindowMode(EUIState_Kostin NewMode)
{
	if (CurrentMode == NewMode) return;
	CurrentMode = NewMode;

	HideAllMenus(); // Скрываем все панели, кроме прицела

	switch (NewMode)
	{
	case EUIState_Kostin::EUIS_Game:
		// Ничего дополнительно не показываем, прицел уже виден
		break;
	case EUIState_Kostin::EUIS_Inventory:
		if (InventoryPanel)
		{
			InventoryPanel->SetVisibility(ESlateVisibility::Visible);
			InventoryPanel->SetKeyboardFocus(); // Передаём фокус инвентарю
		}
		break;
	case EUIState_Kostin::EUIS_PauseMenu:
		/*if (PauseMenuPanel)
		{
			PauseMenuPanel->SetVisibility(ESlateVisibility::Visible);
			PauseMenuPanel->SetKeyboardFocus();
		}*/
		break;
	}
	UpdateInputMode();
}

void UUW_Main_Kostin::NativeConstruct()
{
	Super::NativeConstruct();
	HUD = Cast<AHUD_Kostin>(GetOwningPlayer()->GetHUD());
	if (!HUD) return;
	bIsFocusable = true;
	// if (APlayerController* PC = GetOwningPlayer())
	// {	
	// 	
	// 	PC->OnPossessedPawnChanged.AddDynamic(this, &UUW_Main_Kostin::OnPawnChanged);
	// 	OnPawnChanged(nullptr, PC->GetPawn());
	// }
	
}

void UUW_Main_Kostin::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UUW_Main_Kostin::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	const FKey PressedKey = InKeyEvent.GetKey();
	if (PressedKey == EKeys::I)
	{
		HUD->ToggleInventory();
		
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UUW_Main_Kostin::HideAllMenus()
{
if (InventoryPanel) InventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
}

// void UUW_Main_Kostin::OnPawnChanged(APawn* OldPawn, APawn* NewPawn)
// {
// 	if (NewPawn)
// 	{
// 		 InventoryComponent = NewPawn->GetComponentByClass<UInventoryComponent_Kostin>();
// 	}
// }

void UUW_Main_Kostin::UpdateInputMode()
{


	bool bUIMode = (CurrentMode !=EUIState_Kostin::EUIS_Game);
	//OnInputModeChanged.Broadcast(bUIMode);

	if (bUIMode)
	{
		FInputModeUIOnly InputMode;
		// Устанавливаем фокус на текущую активную панель
		if (CurrentMode == EUIState_Kostin::EUIS_Inventory && InventoryPanel)
		{
			InputMode.SetWidgetToFocus(InventoryPanel->TakeWidget());
			InventoryPanel->SetKeyboardFocus();
		}
			
	//	else if (CurrentMode == EWindowMode::PauseMenu && PauseMenuPanel)
	//		InputMode.SetWidgetToFocus(PauseMenuPanel->TakeWidget());
        
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->SetShowMouseCursor(true);
	}
	else
	{
		FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->SetShowMouseCursor(false);
	}
}


