// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataTypes.h"
#include "Components/ActorComponent.h"
#include "TMS_InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryInitializedSignature);

UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TMS_LS_API UTMS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTMS_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdatedSignature OnInventoryUpdated;
	UPROPERTY(BlueprintAssignable)
	FOnInventoryInitializedSignature OnInventoryInitialized;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ContainerName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FItemSlotData> Slots;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 ContainerSize = 10;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 StartDrag;*/
	
public:
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemSlotData& InItem, bool& OutSuccess);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(FItemSlotData InItem);

	UFUNCTION(BlueprintCallable)
	void DEBUG_PrintSlots();
	
private:
	UFUNCTION()
	bool HasNotFullSlotOfItem(const FName& ItemID, int32& OutIndex);
	UFUNCTION()
	bool FindFirstSlotOfType(int32& OutIndex, const FName InName = FName());

	UFUNCTION()
	bool CreateNewEmptySlotOfType(const FName& ItemID);

	UFUNCTION()
	bool TryToFill(int32 InID, const FItemSlotData& InItem, int32& Overflow);

	int32 GetMaxAmount(FName ItemID);
};
