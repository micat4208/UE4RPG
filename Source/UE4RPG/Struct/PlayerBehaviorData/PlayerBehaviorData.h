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

	// ������ �ڵ�, Npc �ڵ�, ���� �ڵ� ���� ��Ÿ���ϴ�.
	FName Code;

	// ������ ��Ÿ���ϴ�.
	int32 Count;

	// Ư���� ���� �����Ͱ� ����˴ϴ�.
	/// - BH_UseInventory �ൿ �߻� �� �κ��丮 ���� �ε����� �����
	int32 IntegerData1;

public :
	FPlayerBehaviorData(EPlayerBehavior::Type behavior = EPlayerBehavior::BH_None);
	FPlayerBehaviorData(EPlayerBehavior::Type behavior, FName code, int32 count, int32 index);

public :
	// �ڵ带 ����ϴ�.
	FORCEINLINE FName GetCode() const
	{ return Code; }

	// ������ ���� ����ϴ�.
	FORCEINLINE int32 GetItemCount() const
	{ return Count; }

	// �κ��丮 ���� �ε����� ����ϴ�.
	FORCEINLINE int32 GetInventoryItemSlotIndex() const
	{ return IntegerData1; }
};
