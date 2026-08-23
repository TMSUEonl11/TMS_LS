// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_EquipmentComponent.h"

#include "TMS_InventoryComponent.h"
#include "TMS_InventorySubsystem.h"
#include "GameFramework/Character.h"
#include "ItemObjects/ItemObject.h"
#include "TMS_LS/Components/TMS_ArmorComponent.h"
#include "TMS_LS/Components/TMS_WeaponComponent.h"
#include "TMS_LS/Items/Equipment/TMS_BaseArmor.h"

UTMS_EquipmentComponent::UTMS_EquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	for (EEquipmentType ET : TEnumRange<EEquipmentType>())
	{
		EquipmentObjects.FindOrAdd(ET);
		EquipmentActors.FindOrAdd(ET);
	}
}

void UTMS_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	for (EEquipmentType Type : TEnumRange<EEquipmentType>())
	{
		if (UItemObject* Item = *EquipmentObjects.Find(Type))
		{
			if (Item->ItemData.ItemID != NAME_None)
			{
				FEquipmentProcess EquipmentProcess(Item, Type, true);
				AddPendingEquipment(EquipmentProcess);
			}
		}
	}
}

void UTMS_EquipmentComponent::AddPendingEquipment(const FEquipmentProcess& InEP)
{
	EquipmentProcesses.Enqueue(InEP);
	if (!CurrentEquipmentProcess.IsValid())
	{
		NextPendingEquipment();
	}
}

void UTMS_EquipmentComponent::GetEquipmentBySlot(EEquipmentType InSlot, UItemObject*& OutItem,
	AItemEquipment*& OutEquipmentActor)
{
	if (!EquipmentObjects.Contains(InSlot) || !EquipmentActors.Contains(InSlot)) return;
	OutItem = EquipmentObjects[InSlot];
	OutEquipmentActor = EquipmentActors[InSlot];
}

bool UTMS_EquipmentComponent::SaveEquipmentToFile(const FString& FilePath) const
{
	FString Directory = FPaths::GetPath(FilePath);
	IFileManager::Get().MakeDirectory(*Directory, true);
	
	FString JsonString = SerializeToJson();
	
	if (JsonString.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to serialize data to Json"));
		return false;
	}
	
	bool bSaved = FFileHelper::SaveStringToFile(JsonString, *FilePath);
	
	if (bSaved)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully saved data to %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to save data to %s"), *FilePath);
	}
	
	return bSaved;
}

bool UTMS_EquipmentComponent::LoadEquipmentFromFile(const FString& FilePath)
{
	if (!FPaths::FileExists(FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("No save file on path %s"), *FilePath);
		return false;
	}
	
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load save file on path %s"), *FilePath);
		return false;
	}
	
	bool bLoaded =DeserializeFromJson(JsonString);
	if (bLoaded)
	{
	}
	return false;
}

void UTMS_EquipmentComponent::NextPendingEquipment()
{
	OnSlotUpdate.Broadcast(CurrentEquipmentProcess.Slot);
	CurrentEquipmentProcess = FEquipmentProcess();
	if (EquipmentProcesses.IsEmpty()) return;
	EquipmentProcesses.Dequeue(CurrentEquipmentProcess);
	EquipmentProcesses.Pop();

	if (!CurrentEquipmentProcess.IsValid()) NextPendingEquipment();
	
	if (CurrentEquipmentProcess.bEquipment)
	{
		EquipSlot(CurrentEquipmentProcess.Slot, CurrentEquipmentProcess.ItemData);
	}
	else
	{
		UnequipSlot(CurrentEquipmentProcess.Slot);
	}
}

void UTMS_EquipmentComponent::EquipSlot(EEquipmentType InSlot, UItemObject* InItem)
{
	if (!GetWorld()) return;
	OnBeginEquip.Broadcast(InSlot);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	if (InItem->ItemData.ItemID == NAME_None)
	{
		FinishEquip();
		return;
	}

	FItemData ItemData;
	if (UTMS_InventorySubsystem* IS = GetWorld()->GetGameInstance()->GetSubsystem<UTMS_InventorySubsystem>())
	{
		IS->GetItemData(InItem->ItemData.ItemID, ItemData);
	}
	if (ItemData.ItemID == NAME_None)
	{
		FinishEquip();
		return;
	}

	AItemEquipment* EquipmentActor = GetWorld()->SpawnActor<AItemEquipment>(ItemData.ItemClass.Get(), SpawnParams);

	if (!EquipmentActor)
	{
		FinishEquip();
		return;
	}

	EquipmentObjects.Emplace(InSlot, InItem);
	EquipmentActors.Emplace(InSlot, EquipmentActor);

	MoveCurrentItemInInventory();

	ProcessEquip(InSlot);
	OnEquipmentUpdated.Broadcast();
}

void UTMS_EquipmentComponent::UnequipSlot(EEquipmentType InSlot)
{
	if (!EquipmentActors[InSlot]) return;

	OnBeginUnequip.Broadcast(InSlot);
	ProcessUnequip(InSlot);
}

void UTMS_EquipmentComponent::ProcessEquip(EEquipmentType InSlot)
{
	AItemEquipment* ItemEquipment = EquipmentActors[InSlot];
	if (!ItemEquipment || !GetWorld() || !GetOwner())
	{
		FinishEquip();
		return;
	}

	FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetIncludingScale;

	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		FinishEquip();
		return;
	}

	ItemEquipment->AttachToComponent(Player->GetMesh(), Rules, ItemEquipment->SocketName);
	float AnimLength = 1.f;
	if (UAnimMontage* EquipAnim = ItemEquipment->GetMontageByType(EEquipmentAction::EEA_Equip))
	{
		AnimLength = Player->PlayAnimMontage(EquipAnim);
	}

	GetWorld()->GetTimerManager().SetTimer(EquipmentHandle,
		this, &UTMS_EquipmentComponent::FinishEquip,
		AnimLength, false);	
}

void UTMS_EquipmentComponent::ProcessUnequip(EEquipmentType InSlot)
{
	AItemEquipment* EquipmentItem = EquipmentActors[InSlot];
	if (!GetWorld() || !GetOwner() || !EquipmentItem)
	{
		FinishUnequip();
		return;
	}

	UAnimMontage* EquipAnim = EquipmentItem->GetMontageByType(EEquipmentAction::EEA_Unequip);
	float AnimLength = EquipAnim ? EquipAnim->GetPlayLength() : 1.6f;
	if (EquipAnim)
	{
		if (ACharacter* Player = Cast<ACharacter>(GetOwner()))
		{
			Player->GetMesh()->GetAnimInstance()->Montage_Play(EquipAnim);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(EquipmentHandle, this,
		&ThisClass::FinishUnequip, AnimLength, false);
}

void UTMS_EquipmentComponent::FinishEquip()
{
	switch(CurrentEquipmentProcess.Slot)
	{
	case EEquipmentType::EET_Main:
		if (UTMS_WeaponComponent* WC = GetOwner()->GetComponentByClass<UTMS_WeaponComponent>())
		{
			WC->SetCurrentWeapon(Cast<ATMS_BaseWeapon>(EquipmentActors[CurrentEquipmentProcess.Slot]));
		}
		break;
	case EEquipmentType::EET_Armor:
		if (UTMS_ArmorComponent* AC = GetOwner()->GetComponentByClass<UTMS_ArmorComponent>())
		{
			if (ATMS_BaseArmor* ArmorItem = Cast<ATMS_BaseArmor>(EquipmentActors[CurrentEquipmentProcess.Slot]))
			{
				AC->SetEquipment(ArmorItem->EquipmentData);
			}
		}
		break;
	default:
		break;
	}
	if (ACharacter* Player = Cast<ACharacter>(GetOwner()))
	{
		if (UTMS_InventoryComponent* IC =
			Player->GetComponentByClass<UTMS_InventoryComponent>())
		{
			IC->InventoryUpdated();
		}
	}
	
	OnFinishEquip.Broadcast(CurrentEquipmentProcess.Slot);
	NextPendingEquipment();
}

void UTMS_EquipmentComponent::FinishUnequip()
{
	
	switch(CurrentEquipmentProcess.Slot)
	{
	case EEquipmentType::EET_Main:
		if (UTMS_WeaponComponent* WC = GetOwner()->GetComponentByClass<UTMS_WeaponComponent>())
		{
			WC->SetCurrentWeapon(nullptr);
		}
		break;
	case EEquipmentType::EET_Armor:
		if (UTMS_ArmorComponent* AC = GetOwner()->GetComponentByClass<UTMS_ArmorComponent>())
		{
			AC->SetEquipment(nullptr);
		}
		break;
	default:
		break;
	}
	
	if (AActor* EquipActor = EquipmentActors[CurrentEquipmentProcess.Slot])
	{
		EquipActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquipActor->Destroy();
	}

	MoveCurrentItemInInventory();

	EquipmentActors.Emplace(CurrentEquipmentProcess.Slot);
	EquipmentObjects.Emplace(CurrentEquipmentProcess.Slot);
	
	OnFinishUnequip.Broadcast(CurrentEquipmentProcess.Slot);
	NextPendingEquipment();
	OnEquipmentUpdated.Broadcast();
}

void UTMS_EquipmentComponent::MoveCurrentItemInInventory()
{
	if (!CurrentEquipmentProcess.IsValid()) return;
	
	if (ACharacter* Player = Cast<ACharacter>(GetOwner()))
	{
		if (UTMS_InventoryComponent* IC =
			Player->GetComponentByClass<UTMS_InventoryComponent>())
		{
			UItemObject* Item = EquipmentObjects[CurrentEquipmentProcess.Slot];
			if (Item->ItemData.ItemID == NAME_None) return;
			
			if (CurrentEquipmentProcess.bEquipment)
			{
				IC->RemoveItemAsObject(Item);
			}
			else
			{
				IC->AddItemAsObject(Item);
			}
		}
	}
}

FString UTMS_EquipmentComponent::SerializeToJson() const
{
	 TSharedPtr<FJsonObject> JObject = MakeShareable(new FJsonObject);
	 TArray<TSharedPtr<FJsonValue>> JTypeArray;
	
	 for (EEquipmentType Type : TEnumRange<EEquipmentType>())
	 {
	 	TSharedPtr<FJsonObject> ItemJson;
	 	const UItemObject* Item  = EquipmentObjects[Type];
	 	if (Item && Item->ItemData.ItemID != NAME_None)
	 	{
	 		ItemJson=Item->SerializeToJson();
	 	}
	    else
	    {
	    	ItemJson = MakeShareable(new FJsonObject);
	    	ItemJson->SetStringField(UItemObject::JsonKey_ClassName, TEXT(""));
	    	ItemJson->SetStringField(UItemObject::JsonKey_ItemID, TEXT(""));
	    	ItemJson->SetNumberField(UItemObject::JsonKey_Amount, 0);
	    }
	 	JTypeArray.Add(MakeShareable(new FJsonValueObject(ItemJson)));
	 }
	JObject->SetArrayField(TEXT("Equipment"), JTypeArray);
	
	FString OutString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutString);
	FJsonSerializer::Serialize(JObject.ToSharedRef(), Writer);

	return OutString;
}

bool UTMS_EquipmentComponent::DeserializeFromJson(const FString& InJsonString)
{
	TSharedPtr<FJsonObject> JObject;
	int32 Index = 0;
	
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InJsonString);
	if (!FJsonSerializer::Deserialize(JsonReader, JObject) || !JObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON"));	 
		return false;
	}
	const TArray<TSharedPtr<FJsonValue>>* EquipArray;
	if (JObject->TryGetArrayField(TEXT("Equipment"), EquipArray))
	{
		for (EEquipmentType Type : TEnumRange<EEquipmentType>())
		{
			if (Index >= EquipArray->Num())
				break;
				
			TSharedPtr<FJsonValue> Equip = (*EquipArray)[Index];
			TSharedPtr<FJsonObject> EquipObject = Equip->AsObject();
			Index++;
			if (EquipObject.IsValid())
			{
				// Проверяем, есть ли класс
				FString ClassName;
				if (EquipObject->TryGetStringField(UItemObject::JsonKey_ClassName, ClassName) || ClassName.IsEmpty())
				{
					// Создаём объект нужного класса
					UClass* FoundClass = FindObject<UClass>(this, *ClassName);
					if (!FoundClass)
					{
						// Если класс не найден, пробуем загрузить по пути
						FoundClass = LoadClass<UItemObject>(nullptr, *ClassName);
					}
					if (!FoundClass || !FoundClass->IsChildOf(UItemObject::StaticClass()))
					{
						UE_LOG(LogTemp, Warning, TEXT("Unknown class or not UItemObject: %s"), *ClassName);
						continue;
					}
					UItemObject* NewItem = NewObject<UItemObject>(this, FoundClass);
					if (!NewItem)	continue;
					if (!NewItem->DeserializeFromJson(EquipObject)) continue;
					else
					{
					//	EquipSlot(Type,NewItem);
						FEquipmentProcess EquipmentProcess(NewItem, Type, true);
						AddPendingEquipment(EquipmentProcess);
					}
				}
			}
		}
		
		// for (EEquipmentType Type : TEnumRange<EEquipmentType>())
		// {
		// 	if (Index >= EquipArray->Num())
		// 		break;
		//
		// 	TSharedPtr<FJsonValue> Equip = (*EquipArray)[Index];
		// 	TSharedPtr<FJsonObject> EquipObject = Equip->AsObject();
		// 	if (EquipObject.IsValid())
		// 	{
		// 		FItemSlotData NewEquip;
		// 		NewEquip.FromJson(EquipObject);
		// 		EquipSlot(Type,NewEquip);
		// 	}
		// 	++Index;
		// }
		
	/*	for (EEquipmentType Type : TEnumRange<EEquipmentType>())
		{
			if (Index >= EquipArray->Num())
				break;
		
			TSharedPtr<FJsonValue> Equip = (*EquipArray)[Index];
			TSharedPtr<FJsonObject> EquipObject = Equip->AsObject();
			if (EquipObject.IsValid())
			{
				UItemObject Item;
				Item.DeserializeFromJson(EquipObject);
				//FItemSlotData NewEquip;
			//	NewEquip.FromJson(EquipObject);
				//FEquipmentProcess EquipmentProcess()
				FEquipmentProcess EquipmentProcess(&Item, Type, true);
				AddPendingEquipment(EquipmentProcess);
			}
			++Index;
		}*/
	}
	
	return true;
}


