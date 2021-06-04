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

};
