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
	// ������ �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	FName ItemCode;

	// ������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	EItemType ItemType;

	// ������ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	FText ItemName;

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	FText ItemDescription;

	// ������ �̹��� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	FSoftObjectPath ItemImagePath;

	// ���Կ� ���� �� �ִ� �ִ� ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	int32 MaxSlotCount;

	// ������ �Ǹ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "�⺻")
	int32 Price;
};
