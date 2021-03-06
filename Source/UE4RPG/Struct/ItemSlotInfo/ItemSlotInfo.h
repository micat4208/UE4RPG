#pragma once

#include "CoreMinimal.h"
#include "ItemSlotInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FItemSlotInfo
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "아이템 코드")
	FName ItemCode;

	// 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "아이템 개수")
	int32 ItemCount;

	// 슬롯에 저장될 수 있는 최대 개수
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

	// 해당 데이터를 비웁니다/
	FORCEINLINE void Clear()
	{
		ItemCode = FName();
		ItemCount = 0;
		MaxSlotCount = 0;
	}

};
