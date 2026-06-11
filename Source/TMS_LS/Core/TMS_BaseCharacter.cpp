// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_BaseCharacter.h"

// Sets default values
ATMS_BaseCharacter::ATMS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UTMS_HealthComponent>(TEXT("HealthComponent"));

	InventoryComponent = CreateDefaultSubobject<UTMS_InventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void ATMS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(HealthComponent))
	{
		HealthComponent->OnDeath.AddDynamic(this, &ATMS_BaseCharacter::OnDeath);
	}

	
}

// Called every frame
void ATMS_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATMS_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATMS_BaseCharacter::OnDeath()
{
	if (!VaultAnims.IsValid()) return;
	PlayAnimMontage(VaultAnims.DeathMontage);
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->UnPossess();
		PC->StartSpectatingOnly();
		SetLifeSpan(5.f);
	}
}
