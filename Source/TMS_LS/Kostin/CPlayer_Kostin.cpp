// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer_Kostin.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/TMS_HealthComponent_Kostin.h"
#include "Components/TMS_WeaponComponent_Kostin.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/TMS_BaseWeapon_Kostin.h"


ACPlayer_Kostin::ACPlayer_Kostin()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	MotionWarper = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarper");
	
	WeaponComponent_Kostin = CreateDefaultSubobject<UTMS_WeaponComponent_Kostin>("WeaponComponent");
	HealthComponent_Kostin = CreateDefaultSubobject<UTMS_HealthComponent_Kostin>("HealthComponent");
	InventoryComponent_Kostin = CreateDefaultSubobject<UInventoryComponent_Kostin>("InventoryComponent");
	//TargetFOV = Camera->FieldOfView;
	
}

void ACPlayer_Kostin::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;
	PHUD = Cast<AHUD_Kostin>(PlayerController->GetHUD());
	if (!PHUD) return;
}

void ACPlayer_Kostin::OnMoveInput(const FInputActionValue& InputActionValue)
{
	MoveInput =InputActionValue.Get<FVector2D>().GetSafeNormal();
	float InputScale = MoveInput.Length();


	FVector Forward = GetControlRotation().Vector().GetSafeNormal2D();
	FVector Right = Forward.Cross(FVector::UpVector);

	FVector Dir = Forward * MoveInput.X + Right * MoveInput.Y;

	AddMovementInput(Dir, InputScale);
	//GetCharacterMovement()->bUseControllerDesiredRotation = MoveInput.Length() > 0.f;
	//bUseControllerRotationYaw = MoveInput.Length() == 0.f;
	
}

void ACPlayer_Kostin::OnLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D LookInput = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(LookInput.Y);
	AddControllerYawInput(LookInput.X);
	
	CurrentRotation.Yaw= FMath::Clamp(CurrentRotation.Yaw +LookInput.X, -60.0f, 60.0f);
	CurrentRotation.Pitch= FMath::Clamp(CurrentRotation.Pitch -LookInput.Y, -10.0f, 20.0f);
	
	//CurrentRotation.Yaw = CurrentRotation.Yaw +LookInput.X;//FMath::Clamp(CurrentRotation.Yaw +LookInput.X, -60.0f, 60.0f);

	//SpringArm->SetWorldRotation(CurrentRotation);
	
	
	//SpringArm->AddWorldRotation(FRotator( LookInput.Y, LookInput.X, 0.0f));
	

	// UE_LOG(LogTemp, Display, TEXT("OnLookInput : %s"), *CurrentRotation.ToString());
	// double Rotation = CurrentRotation.Yaw +LookInput.X;
	// if (Rotation < -30.0f || Rotation > 30.0f)
	// {
	// 	SetActorRotation(CurrentRotation);
	// 	CurrentRotation.Yaw = CurrentRotation.Yaw-Rotation;
	// 	UE_LOG(LogTemp, Display, TEXT("OnLookInput_2 : %s"), *CurrentRotation.ToString());
	// }
	//CurrentRotation.Yaw = Rotation;
	
	
}

void ACPlayer_Kostin::OnSprintInput(const FInputActionValue& InputActionValue)
{
	bool ToSprint = InputActionValue.Get<bool>();
}

void ACPlayer_Kostin::UseItem(const FInputActionValue& InputActionValue)
{
	if (!WeaponComponent_Kostin|| !WeaponComponent_Kostin->CurrentWeapon) return;
	bool bUseItem = InputActionValue.Get<bool>();
	
	WeaponComponent_Kostin->CurrentWeapon->Fire_Input(bUseItem);
}

void ACPlayer_Kostin::OnInventoryInput(const FInputActionValue& InputActionValue)
{
	if (!PHUD) return;
	PHUD->ToggleInventory();
}


void ACPlayer_Kostin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!InputContext || !IsValid(InputData)) return;
	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;
	
	UEnhancedInputLocalPlayerSubsystem* EIS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());
	if (!EIS) return;
	
	EIS->ClearAllMappings();
	EIS->AddMappingContext(InputContext, 100);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC) return;

	 EIC->BindAction(InputData->MoveInput, ETriggerEvent::Triggered, this, &ACPlayer_Kostin::OnMoveInput);
	 EIC->BindAction(InputData->LookInput, ETriggerEvent::Triggered, this, &ACPlayer_Kostin::OnLookInput);
	 EIC->BindAction(InputData->SprintInput, ETriggerEvent::Triggered, this, &ACPlayer_Kostin::OnSprintInput);
	// EIC->BindAction(InputData->CrouchInput, ETriggerEvent::Triggered, this, &ACPlayer_Kostin::OnCrouchInput);
	//
	 EIC->BindAction(InputData->JumpInput, ETriggerEvent::Started, this, &ACPlayer_Kostin::Jump);
	 EIC->BindAction(InputData->JumpInput, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	//
	 EIC->BindAction(InputData->MainInput, ETriggerEvent::Triggered, this, &ACPlayer_Kostin::UseItem);
	EIC->BindAction(InputData->InventoryInput, ETriggerEvent::Triggered, this, &ACPlayer_Kostin::OnInventoryInput);
}

void ACPlayer_Kostin::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (!GetCharacterMovement())
	{
		return;
	}
	FVector LandingVelocity = GetVelocity();
	float FallSpeed = FMath::Abs(LandingVelocity.Z);
	UE_LOG(LogTemp, Display, TEXT("Landed : %f"), FallSpeed);
	if (FallSpeed > FallDamageVelocity)
	{
		float AppliedDamage = (FallSpeed - FallDamageVelocity) * 0.25;
		AppliedDamage = FMath::Max(0.0f, AppliedDamage);
		if (AppliedDamage > 0.0f)
		{
			TSubclassOf<UDamageType> FallDamageType;
			TakeDamage(AppliedDamage, FDamageEvent(FallDamageType), GetController(), this);	
		}
	}
	
}
