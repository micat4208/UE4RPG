#pragma once

#include "CoreMinimal.h"
#include "ItemSlotInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FItemSlotInfo
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "������ �ڵ�")
	FName ItemCode;

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "������ ����")
	int32 ItemCount;

	// ���Կ� ����� �� �ִ� �ִ� ����
	int32 MaxSlotCount;

public :
	FItemSlotInfo();
	FItemSlotInfo(FName itemCode, int32 itemCount = 0, int32 maxSlotCount = 0);

	FORCEINLINE bool IsSameItem(const FName& itemCode) const
	{ return this->ItemCode == itemCode; }

	FORCEINLINE bool IsSameItem(const FItemSlotInfo& itemSlotInfo) const
	{ return IsSameItem(itemSlotInfo.ItemCode); }

	FORCEINLINE bool IsEmpty() const
	{ return ItemCode.IsNone(); }

};
