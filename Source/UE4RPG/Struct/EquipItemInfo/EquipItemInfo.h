#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Enum/PartsType.h"

#include "EquipItemInfo.generated.h"

// 하나의 장비 아이템 정보를 나타냅니다.
USTRUCT(BlueprintType)
struct UE4RPG_API FEquipItemInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 장착 가능 부위
	UPROPERTY(EditAnywhere, BlueprintType)
	EPartsType PartsType;

	// Mesh 경로
	UPROPERTY(EditAnywhere, BlueprintType)
	FSoftObjectPath MeshPath;

	// 함께 사용되는 Mesh 경로
	UPROPERTY(EditAnywhere, BlueprintType)
	FSoftObjectPath SetMeshPath;
};
