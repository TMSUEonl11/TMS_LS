// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface_Kostin.h"
#include "GameFramework/Actor.h"
#include "Item/ItemObject_Kostin.h"
#include "Utilities/GameInstanceSubsystem_Kostin.h"
#include "LootItem_Kostin.generated.h"

UCLASS()
class TMS_LS_API ALootItem_Kostin : public AActor, public IInteractInterface_Kostin
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALootItem_Kostin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	TObjectPtr<UItemObject_Kostin> HoldingItem;
	
	UPROPERTY()
	UGameInstanceSubsystem_Kostin* IS;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<UItemObject_Kostin> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 1;
protected:
	void InitLoot();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool InteractCall_Implementation(APlayerController* InPC) override;
	
	//virtual bool InteractCall_Implementation(APlayerController * PC) override;
};