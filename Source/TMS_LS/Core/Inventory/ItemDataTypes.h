#pragma once

#include "CoreMinimal.h"
#include "ItemDataTypes.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor=true))
enum class ELootType : uint8
{
	ELT_None = 0 UMETA(Hidden),
	ELT_Weapon = 1 << 0 UMETA(DisplayName = "Weapon"),
	ELT_Ammo = 1 << 1 UMETA(DisplayName = "Ammo"),
	ELT_Health = 1 << 2 UMETA(DisplayName = "Health"),
};

USTRUCT(BlueprintType)
struct FItemSlotData
{
	GENERATED_BODY()

	FItemSlotData()
	{
		ItemID = FName();
		Amount = 0;
	}
	
	FItemSlotData(FName InName, int32 InAmount)
	{
		ItemID = InName;
		Amount = InAmount;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID = FName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemID;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELootType Type = ELootType::ELT_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmount = 64;
};