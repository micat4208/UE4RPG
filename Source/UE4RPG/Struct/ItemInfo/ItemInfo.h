#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/ItemType.h"
#include "ItemInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FItemInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FName ItemCode;

	// 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	EItemType ItemType;

	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FText ItemName;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FText ItemDescription;

	// 아이템 이미지 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FSoftObjectPath ItemImagePath;

	// 슬롯에 담을 수 있는 최대 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	int32 MaxSlotCount;

	// 아이템 판매 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	int32 Price;

public :
	FItemInfo();

	FORCEINLINE bool IsEmpty() const
	{ return ItemCode.IsNone(); }
};
