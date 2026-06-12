// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataTypes.h"
#include "Engine/DataAsset.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TMS_LS_API UItemObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;
	
	UPROPERTY()
	int32 Amount = 0;
};
