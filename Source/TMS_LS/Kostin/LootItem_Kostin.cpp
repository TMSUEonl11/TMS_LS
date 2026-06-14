// Fill out your copyright notice in the Description page of Project Settings.


#include "LootItem_Kostin.h"
#include "TMS_LS/Kostin/Item/ItemData_Kostin.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"



// Sets default values
ALootItem_Kostin::ALootItem_Kostin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Root->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

void ALootItem_Kostin::InitLoot()
{
	FItemData_Kostin ItemData;
	if (IS->GetItemDataByID(ItemID,ItemData))
	{

		HoldingItem = NewObject<UItemObject_Kostin>(this);
		if (!HoldingItem) return;
		HoldingItem->ItemData=ItemData;
		if (HoldingItem->ItemData.PreviewMesh.IsPending())
		{
			FStreamableManager& SM = UAssetManager::GetStreamableManager();
			SM.RequestAsyncLoad(
				HoldingItem->ItemData.PreviewMesh.ToSoftObjectPath(),
				FStreamableDelegate::CreateLambda([this]()
				{
					if (Mesh && HoldingItem)  
					{
						Mesh->SetStaticMesh(HoldingItem->ItemData.PreviewMesh.Get());
					}
				})
			);
		}
		else
		{
			Mesh->SetStaticMesh(HoldingItem->ItemData.PreviewMesh.Get());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item с ID %d не найден в таблице"), ItemID);
	}
}

// Called when the game starts or when spawned
void ALootItem_Kostin::BeginPlay()
{
	Super::BeginPlay();
	IS = GetGameInstance()->GetSubsystem<UGameInstanceSubsystem_Kostin>();
	if (!IS) return;
	InitLoot();
}

// Called every frame
void ALootItem_Kostin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ALootItem_Kostin::InteractCall_Implementation(APlayerController* InPC)
{
	IInteractInterface_Kostin::InteractCall_Implementation(InPC);
	if (!InPC)return false;
	Amount=IS->AddItem(InPC,ItemID,Amount);
	if (!Amount)Destroy();
	return true;
}




