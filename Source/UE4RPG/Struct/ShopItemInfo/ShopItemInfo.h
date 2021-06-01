#pragma once

#include "CoreMinimal.h"
#include "ShopItemInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FShopItemInfo
{
	GENERATED_USTRUCT_BODY()

public:

	// 판매 아이템 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemCode;

	// 판매 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;
};
