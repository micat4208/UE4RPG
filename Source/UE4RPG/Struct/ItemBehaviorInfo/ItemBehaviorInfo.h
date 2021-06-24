#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/CharacterStatusAttribute.h"
#include "ItemBehaviorInfo.generated.h"

// 아이템 동작 정보를 나타내기 위한 구조체
USTRUCT(BlueprintType)
struct UE4RPG_API FItemBehaviorInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// 아이템 동작들을 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterStatusAttribute, float> ItemBehaviors;


};
