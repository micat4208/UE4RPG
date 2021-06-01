#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Struct/ShopItemInfo/ShopItemInfo.h"
#include "ShopInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FShopInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 창 제목으로 표시될 상점 이름을 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ShopName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FShopItemInfo> ShopItems;

};
