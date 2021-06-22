#pragma once

#include "CoreMinimal.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "Enum/CharacterStatusAttribute.h"

#include "PlayerCharacterInfo.generated.h"

// 플레이어 캐릭터의 기반 정보를 나타낼 때 사용되는 구조체입니다.
USTRUCT()
struct UE4RPG_API FPlayerCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public:
	
	// 인벤토리 슬롯 개수
	UPROPERTY()
	int32 InventorySlotCount;

	// 소지중인 아이템
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// 소지금
	UPROPERTY()
	int32 Silver;

	// 상태 속성
	UPROPERTY()
	TMap<ECharacterStatusAttribute, float> StatusAttributes;

public :
	FPlayerCharacterInfo();


};
