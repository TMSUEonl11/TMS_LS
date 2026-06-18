// Fill out your copyright notice in the Description page of Project Settings.


#include "TMS_EnemyControllerBase.h"
#include "GameFramework/Character.h"
#include "TMS_AIPerception.h"
#include "TMS_EnemyCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ATMS_EnemyControllerBase::ATMS_EnemyControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Perception = CreateDefaultSubobject<UTMS_AIPerception>("Perception");
}

// Called when the game starts or when spawned
void ATMS_EnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

AActor* ATMS_EnemyControllerBase::GetTargetActor()
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(TargetEnemyKeyName));
}

FVector ATMS_EnemyControllerBase::GetTargetHeadBoneLocation()
{
	FVector DefaultLocation = GetPawn()->GetActorLocation();
	if (!GetTargetActor()) return DefaultLocation;

	ACharacter* Char = Cast<ACharacter>(GetTargetActor());
	if (!Char) return DefaultLocation;

	return Char->GetMesh()->GetBoneLocation(FName("head"));
}

// Called every frame
void ATMS_EnemyControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetFocalPoint(GetTargetHeadBoneLocation());
	//SetFocus(GetTargetActor());
}

void ATMS_EnemyControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ATMS_EnemyCharacterBase* EnemyPawn = Cast<ATMS_EnemyCharacterBase>(InPawn))
	{
		if (EnemyPawn->BehaviorTree)
		{
			RunBehaviorTree(EnemyPawn->BehaviorTree);
		}
	}
}

