#pragma once

#include "CoreMinimal.h"
#include "TMS_DataTypes.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FTMS_VaultAnimData
{
	GENERATED_BODY()

	FTMS_VaultAnimData()
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

	bool IsValid() const
	{
		return (GetUpMontage && ClimbMontage && JumpDownMontage && VaultMontage);
	}
};