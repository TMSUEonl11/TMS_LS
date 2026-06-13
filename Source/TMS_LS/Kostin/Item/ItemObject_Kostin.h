// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData_Kostin.h"
#include "UObject/Object.h"
#include "ItemObject_Kostin.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TMS_LS_API UItemObject_Kostin : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData_Kostin ItemData;
};
