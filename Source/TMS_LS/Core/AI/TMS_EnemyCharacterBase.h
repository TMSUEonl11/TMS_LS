// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMS_LS/Core/TMS_BaseCharacter.h"
#include "TMS_EnemyCharacterBase.generated.h"

class ATMS_AIPatrolPath;

UCLASS()
class TMS_LS_API ATMS_EnemyCharacterBase : public ATMS_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATMS_EnemyCharacterBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI")
	TSoftObjectPtr<ATMS_AIPatrolPath> PatrolPath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};
