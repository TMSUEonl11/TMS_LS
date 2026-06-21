// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TMS_EnemyControllerBase.generated.h"

class UTMS_AIPerception;

UCLASS()
class TMS_LS_API ATMS_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMS_EnemyControllerBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UTMS_AIPerception> Perception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName TargetEnemyKeyName = "TargetActor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName PatrolPathKeyName = "PatrolPath";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AActor* GetTargetActor();
	FVector GetTargetHeadBoneLocation();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
};
