#pragma once

#include "CoreMinimal.h"
#include "CharacterStatusAttribute.generated.h"

// 캐릭터 상태 속성을 나타내기 위한 열거 형식입니다.
UENUM(BlueprintType)
enum class ECharacterStatusAttribute : uint8
{
	MaxHp,
	Hp
};
