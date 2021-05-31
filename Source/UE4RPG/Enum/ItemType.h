#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

// 아이템 타입을 나타낼 때 사용되는 열거 형식입니다.
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EtCetera		UMETA(DisplayName = 기타 아이템),
	Consumption		UMETA(DisplayName = 소비 아이템),
	Equipment		UMETA(DisplayName = 장비 아이템)
};
