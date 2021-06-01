#pragma once

#include "CoreMinimal.h"
#include "SlotType.generated.h"

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	ShopItemSlot		UMETA(DisplayName = 상점 슬롯),
	InventorySlot		UMETA(DisplayName = 인벤토리 슬롯),
};