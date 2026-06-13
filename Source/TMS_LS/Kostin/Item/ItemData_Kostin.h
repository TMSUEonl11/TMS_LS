#pragma once

#include "CoreMinimal.h"
#include "ItemData_Kostin.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor=true))
enum class ELootType_Kostin : uint8
{
	ELT_None = 0 UMETA(Hidden),
	ELT_Weapon = 1 << 0 UMETA(DisplayName = "Weapon"),
	ELT_Ammo = 1 << 1 UMETA(DisplayName = "Ammo"),
	ELT_Health = 1 << 2 UMETA(DisplayName = "Health"),
};

USTRUCT(BlueprintType)
struct FItemSlotData_Kostin
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TypeID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};


USTRUCT(BlueprintType)
struct FSlotData_Kostin
{
	GENERATED_BODY()

	FSlotData_Kostin()
	{
		SlotID = -1;
		ItemSlotData.ItemID = -1;
		ItemSlotData.TypeID = -1;
		ItemSlotData.Amount = 0;
	}
	
	FSlotData_Kostin(int32 InID, int32 InType,  int32 InAmount)
	{
		ItemSlotData.ItemID = InID;
		ItemSlotData.TypeID = InType;
		ItemSlotData.Amount = InAmount;
	}
	
	int32 GetSlotID()
	{
		return SlotID;
	}
	
	void SetSlotID(int inSlotID)
	{
		 SlotID=inSlotID;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemSlotData_Kostin ItemSlotData;
};




USTRUCT(BlueprintType)
struct FItemData_Kostin : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ItemID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> PreviewMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AActor> ItemClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ELootType Type = ELootType::ELT_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmount = 64;
};