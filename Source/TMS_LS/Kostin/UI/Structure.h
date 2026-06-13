#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EUIState_Kostin : uint8
{
	EUIS_Game,           // Активен геймплей, виден только прицел
	EUIS_Inventory,      // Открыт инвентарь, нужна мышь
	EUIS_PauseMenu       // Открыто меню паузы, нужна мышь
};
