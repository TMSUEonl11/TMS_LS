// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_HealthComponent_Kostin.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "TMS_LS/Core/TMS_Player.h"
#include "TMS_LS/Core/Data/TMS_MovementData.h"

UTMS_HealthComponent_Kostin::UTMS_HealthComponent_Kostin()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UTMS_HealthComponent_Kostin::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	SetStamina(MaxStamina);

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UTMS_HealthComponent_Kostin::OnTakeDamage);
	}
	
}

void UTMS_HealthComponent_Kostin::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bDead || Damage < 0.f) return;

	
	UE_LOG(LogTemp, Display, TEXT("ResultDamage: %f"), Damage);
	SetHealth(GetHealth() - Damage);
}


// Called every frame
void UTMS_HealthComponent_Kostin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bSprinting)
	{
		ReduceStamina(DeltaTime);
	}
	else
	{
		GainStamina(DeltaTime);
	}
	// ...
}

void UTMS_HealthComponent_Kostin::SetHealth(float NewValue)
{
	Health = FMath::Clamp(NewValue, 0, MaxHealth);
	if (Health <= 0.f)
	{
		bDead = true;
		OnDeath.Broadcast();
	}
}

void UTMS_HealthComponent_Kostin::SetStamina(float NewValue)
{
	Stamina = FMath::Clamp(NewValue, 0, MaxStamina);
}

void UTMS_HealthComponent_Kostin::GainStamina(float DeltaTime)
{
	if (!MovementData || bCooldown) return;

	SetStamina(GetStamina() + DeltaTime * MovementData->StaminaGainPerSecond);
}

void UTMS_HealthComponent_Kostin::ReduceStamina(float DeltaTime)
{
	if (!MovementData) return;
	SetStamina(GetStamina() - DeltaTime * MovementData->StaminaCostPerSecond);

	if (GetStamina() <= 0)
	{
		SprintInput(false);
	}
}

void UTMS_HealthComponent_Kostin::SprintInput(bool InValue)
{
	if (!GetWorld()) return;
	if (InValue)
	{
		bCooldown = true;
		if (GetWorld()->GetTimerManager().IsTimerActive(CoolDownHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(CoolDownHandle);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(CoolDownHandle,
			this, &UTMS_HealthComponent_Kostin::FinishCooldown, MovementData->StaminaCooldown);
	}
	
	if (!CanSprint())
	{
		bSprinting = false;
		return;
	}

	bSprinting = InValue;
	
	ATMS_Player* Player = Cast<ATMS_Player>(GetOwner());
	if (!Player) return;
	
	UCharacterMovementComponent* MovementComponent = Player->GetCharacterMovement();
	if (!MovementComponent) return;

	MovementComponent->MaxWalkSpeed = bSprinting ? MovementData->RunSpeed : MovementData->WalkSpeed;
	Player->Camera->SetFieldOfView(bSprinting ? MovementData->RunFOV : MovementData->WalkFOV);

}

bool UTMS_HealthComponent_Kostin::CanSprint()
{
	if (!IsValid(MovementData)) return false;
	return true;
}

void UTMS_HealthComponent_Kostin::FinishCooldown()
{
	bCooldown = false;
}
