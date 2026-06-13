// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DeveloperSettings_Kostin.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, Displayname = "DeveloperSettings_Kostin")
class TMS_LS_API UDeveloperSettings_Kostin : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UDeveloperSettings_Kostin(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	static const UDeveloperSettings_Kostin* Get();
	
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> ItemDataTable_Kostin;
	
};
