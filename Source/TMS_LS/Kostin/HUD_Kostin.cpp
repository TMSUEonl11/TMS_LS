// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Kostin.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

void AHUD_Kostin::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}
void AHUD_Kostin::BeginPlay()
{
	Super::BeginPlay();
	if (!MainWidgetClass)return;
	MainWidget = CreateWidget<UUW_Main_Kostin>(GetWorld(), MainWidgetClass);
	
	if (MainWidget)
	{
		MainWidget->AddToPlayerScreen(0); // ZOrder = 0
		MainWidget->InitializeWidget();
		// Подписываемся на событие смены режима ввода
		//MainWidget->OnInputModeChanged.AddDynamic(this, &AMyHUD::OnInputModeChanged);
	}
	
}

void AHUD_Kostin::DrawCrosshair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	FVector2D Center = FVector2D(SizeX / 2, SizeY / 2);
	const FLinearColor LineColor = FLinearColor::Green;
	float Radius = 30.0f;
	int32 NumSegments = 20;
	
	float AngleStep = 2.0f * PI / NumSegments;
	FVector2D PreviousPoint = Center + FVector2D(Radius, 0.0f);
	
	for (int32 i = 1; i <= NumSegments; i++)
	{
		float Angle = i * AngleStep;
		FVector2D CurrentPoint = Center + FVector2D(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius);
		DrawLine(PreviousPoint.X, PreviousPoint.Y, CurrentPoint.X, CurrentPoint.Y, LineColor);
		PreviousPoint = CurrentPoint;
	}
}

void AHUD_Kostin::ToggleInventory()
{
	if (!MainWidget) return;
	if (MainWidget->GetCurrentMode() == EUIState_Kostin::EUIS_Inventory)
	{
		MainWidget->SetWindowMode(EUIState_Kostin::EUIS_Game);
		MainWidget->HideAllMenus();
	}
		
	else
		MainWidget->SetWindowMode(EUIState_Kostin::EUIS_Inventory);
}

void AHUD_Kostin::TogglePauseMenu()
{
}

