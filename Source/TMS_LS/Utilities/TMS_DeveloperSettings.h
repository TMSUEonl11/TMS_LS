// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TMS_DeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, Displayname = "TMS_DeveloperSettings")
class TMS_LS_API UTMS_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UTMS_DeveloperSettings(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	static const UTMS_DeveloperSettings* Get();

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> ItemDataTable;
	
};
