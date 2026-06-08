// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter_Kostin.h"

// Sets default values
ACCharacter_Kostin::ACCharacter_Kostin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACCharacter_Kostin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCharacter_Kostin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCharacter_Kostin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

