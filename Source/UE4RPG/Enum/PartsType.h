#pragma once

#include "CoreMinimal.h"
#include "PartsType.generated.h"

// 파츠 타입을 나타내기 위한 열거 형식입니다.
UENUM(BlueprintType)
enum class EPartsType : uint8
{
	PT_Hair			= 10	UMETA(DisplayName = 헤어),
	PT_Head			= 20	UMETA(DisplayName = 머리),
	PT_Top			= 30	UMETA(DisplayName = 상의),
	PT_Bottom		= 40	UMETA(DisplayName = 하의),
	PT_Glove		= 50	UMETA(DisplayName = 장갑),
	PT_LeftGlove	= 60	UMETA(DisplayName = 왼쪽 장갑),
	PT_RightGlove	= 70	UMETA(DisplayName = 오른쪽 장갑),
	PT_Shoes		= 80	UMETA(DisplayName = 신발),
	PT_Weapon		= 90	UMETA(DisplayName = 무기)
};
