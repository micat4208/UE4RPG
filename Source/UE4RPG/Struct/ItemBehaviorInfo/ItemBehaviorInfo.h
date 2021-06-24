#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/CharacterStatusAttribute.h"
#include "ItemBehaviorInfo.generated.h"

// ������ ���� ������ ��Ÿ���� ���� ����ü
USTRUCT(BlueprintType)
struct UE4RPG_API FItemBehaviorInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// ������ ���۵��� ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterStatusAttribute, float> ItemBehaviors;


};
