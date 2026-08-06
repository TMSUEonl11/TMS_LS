#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "TMS_AIPatrolPath.generated.h"

UCLASS()
class TMS_LS_API ATMS_AIPatrolPath : public AActor
{
	GENERATED_BODY()
public:
	ATMS_AIPatrolPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> WaitArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentIndex = 0;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetLocationAtCurrentIndex()
	{
		CurrentIndex %= SplineComponent->GetNumberOfSplinePoints();
		return SplineComponent->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);
	}

	UFUNCTION(BlueprintCallable, CallInEditor)
	void InitWaitArray();

	UFUNCTION(BlueprintCallable)
	void OnReachPoint()
	{
		CurrentIndex = (CurrentIndex+1) % SplineComponent->GetNumberOfSplinePoints();
	}
};
