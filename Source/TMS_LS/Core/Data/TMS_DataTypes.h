#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
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

UENUM(BlueprintType)
enum class EWeaponActionType : uint8
{
	EWAT_Main,
	EWAT_Secondary,
	EWAT_Reload,
	EWAT_MAX UMETA(Hidden)
};
UENUM(BlueprintType)
enum ETeamType : uint8
{
	ETT_Player,
	ETT_NPC,
	ETT_Bandits,
	ETT_Mercenaries,
	ETT_MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FTeamAffiliation
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<ETeamType>, TEnumAsByte<ETeamAttitude::Type>> TeamAttitude;
};


USTRUCT(BlueprintType)
struct FWeaponAnimData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> CAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> WAnim;
	
};

