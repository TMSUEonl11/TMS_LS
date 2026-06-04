#pragma once

#include "CoreMinimal.h"
#include "TMS_DataTypes.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FTMS_AnimData
{
	GENERATED_BODY()

	FTMS_AnimData()
	{
		
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> GetUpMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> ClimbMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> JumpDownMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> VaultMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	bool IsValid() const
	{
		return (GetUpMontage && ClimbMontage && JumpDownMontage && VaultMontage && DeathMontage);
	}
};