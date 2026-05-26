// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_AttributeSet.h"

#include "Net/UnrealNetwork.h"

UTMS_AttributeSet::UTMS_AttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Stamina = 100.f;
	MaxStamina = 100.f;
	Armor = 100.f;
	MaxArmor = 100.f;
}

void UTMS_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTMS_AttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UTMS_AttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UTMS_AttributeSet, Stamina, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UTMS_AttributeSet, MaxStamina, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UTMS_AttributeSet, Armor, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UTMS_AttributeSet, MaxArmor, COND_None, REPNOTIFY_OnChanged);
}
