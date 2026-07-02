// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_Main.h"

#include "TMS_Pause.h"
#include "Kismet/GameplayStatics.h"

void UTMS_Main::NativeConstruct()
{
	Super::NativeConstruct();
	check(AttributePanel);

	ATMS_HUD* HUD = Cast<ATMS_HUD>(GetOwningPlayer()->GetHUD());
	if (HUD)
	{
		HUD->OnUIStateChanged.AddDynamic(this, &UTMS_Main::OnUIStateChanged);
	}
}

void UTMS_Main::OnUIStateChanged_Implementation(EUIState InNewState)
{
	CurrentUIState = InNewState;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	if (PauseWidget)
	{
		PauseWidget->RemoveFromParent();
		PauseWidget = nullptr;
	}
	
	switch (CurrentUIState)
	{
	case EUIState::EUIS_Game:
		{
			FInputModeGameOnly InputMode;
			GetOwningPlayer()->SetInputMode(InputMode);
			GetOwningPlayer()->SetShowMouseCursor(false);
			break;
		}
	case EUIState::EUIS_Pause:
		if (IsValid(PauseWidgetClass))
		{
			PauseWidget = Cast<UTMS_Pause>(CreateWidget(GetOwningPlayer(), PauseWidgetClass));
			if (PauseWidget)
			{
				PauseWidget->AddToViewport(1);
				UGameplayStatics::SetGamePaused(GetWorld(), true);
			}
		}
	case EUIState::EUIS_Loot:
	case EUIState::EUIS_Equipment:
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(this->TakeWidget());
			GetOwningPlayer()->SetInputMode(InputMode);
			GetOwningPlayer()->SetShowMouseCursor(true);
			this->SetKeyboardFocus();
			break;
		}
	}
}
