// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_Player.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATMS_Player::ATMS_Player()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 250.f;
	SpringArm->SocketOffset = FVector(0.f, 100.f, 50.f);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	TargetFOV = Camera->FieldOfView;
}

void ATMS_Player::BeginPlay()
{
	Super::BeginPlay();
}

bool ATMS_Player::CanSprint()
{
	return Super::CanSprint();
}

void ATMS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATMS_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!InputContext || !IsValid(InputData)) return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;

	UEnhancedInputLocalPlayerSubsystem* EIS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());
	if (!EIS) return;

	EIS->ClearAllMappings();
	EIS->AddMappingContext(InputContext, 100);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC) return;

	EIC->BindAction(InputData->MoveInput, ETriggerEvent::Triggered, this, &ATMS_Player::OnMoveInput);
	EIC->BindAction(InputData->LookInput, ETriggerEvent::Triggered, this, &ATMS_Player::OnLookInput);
	EIC->BindAction(InputData->SprintInput, ETriggerEvent::Triggered, this, &ATMS_Player::OnSprintInput);
	EIC->BindAction(InputData->CrouchInput, ETriggerEvent::Triggered, this, &ATMS_Player::OnCrouchInput);

	EIC->BindAction(InputData->JumpInput, ETriggerEvent::Started, this, &ACharacter::Jump);
	EIC->BindAction(InputData->JumpInput, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
}

void ATMS_Player::OnMoveInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("OnMoveInput : %s"), *Value.ToString());
	MoveInput = Value.Get<FVector2D>().GetSafeNormal();
	float InputScale = MoveInput.Length();
	

	FVector Forward = GetControlRotation().Vector().GetSafeNormal2D();
	FVector Right = Forward.Cross(FVector::UpVector);

	FVector Dir = Forward * MoveInput.X + Right * MoveInput.Y;

	AddMovementInput(Dir, InputScale);
}

void ATMS_Player::OnLookInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("OnLookInput : %s"), *Value.ToString());
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerPitchInput(LookInput.Y);
	AddControllerYawInput(LookInput.X);
}

void ATMS_Player::OnSprintInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("OnSprintInput : %s"), *Value.ToString());
	bool ToSprint = Value.Get<bool>();

	if (!CanSprint())
	{
		bSprinting = false;
		return;
	}

	bSprinting = ToSprint;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (!MovementComponent) return;

	MovementComponent->MaxWalkSpeed = bSprinting ? MovementData->RunSpeed : MovementData->WalkSpeed;
	Camera->SetFieldOfView(bSprinting ? MovementData->RunFOV : MovementData->WalkFOV);
}

void ATMS_Player::OnCrouchInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("OnCrouchInput : %s"), *Value.ToString());
	if (!CanCrouch()) return;
	
 	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (!MovementComponent) return;
	
	MovementComponent->IsCrouching() ? MovementComponent->Crouch() : MovementComponent->UnCrouch();
	bCrouching = MovementComponent->IsCrouching();
}
