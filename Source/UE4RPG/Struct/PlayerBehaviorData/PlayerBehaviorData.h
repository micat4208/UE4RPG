#pragma once

#include "CoreMinimal.h"
#include "Enum/PlayerBehavior.h"
#include "PlayerBehaviorData.generated.h"


USTRUCT()
struct UE4RPG_API FPlayerBehaviorData
{
	GENERATED_USTRUCT_BODY()

public:
	EPlayerBehavior::Type Behavior;

	// 아이템 코드, Npc 코드, 몬스터 코드 등을 나타냅니다.
	FName Code;

	// 수량을 나타냅니다.
	int32 Count;

	// 특정한 정수 데이터가 저장됩니다.
	/// - BH_UseInventory 행동 발생 시 인벤토리 슬롯 인덱스가 저장됨
	int32 IntegerData1;

public :
	FPlayerBehaviorData(EPlayerBehavior::Type behavior = EPlayerBehavior::BH_None);
	FPlayerBehaviorData(EPlayerBehavior::Type behavior, FName code, int32 count, int32 index);

public :
	// 코드를 얻습니다.
	FORCEINLINE FName GetCode() const
	{ return Code; }

	// 아이템 수를 얻습니다.
	FORCEINLINE int32 GetItemCount() const
	{ return Count; }

	// 인벤토리 슬롯 인덱스를 얻습니다.
	FORCEINLINE int32 GetInventoryItemSlotIndex() const
	{ return IntegerData1; }
};
