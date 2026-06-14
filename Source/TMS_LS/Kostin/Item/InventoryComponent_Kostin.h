// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData_Kostin.h"
#include "Components/ActorComponent.h"
#include "TMS_LS/Kostin/Utilities/GameInstanceSubsystem_Kostin.h"
#include "InventoryComponent_Kostin.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryInitializedSignature_Kostin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdatedSignature_Kostin);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TMS_LS_API UInventoryComponent_Kostin : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent_Kostin();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnInventoryInitializedSignature_Kostin OnInventoryInitialized;
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdatedSignature_Kostin OnInventoryUpdated;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 ContainerSize = 10;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FSlotData_Kostin> Slots;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	int32 AddItem(int32 ItemID, int32 Amount=1);
	
	int32 GetMaxAmount(int32 ItemID);
	
	UPROPERTY()
	UGameInstanceSubsystem_Kostin* IS;
};

