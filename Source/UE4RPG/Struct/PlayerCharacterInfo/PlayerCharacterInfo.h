#pragma once

#include "CoreMinimal.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "Enum/CharacterStatusAttribute.h"

#include "PlayerCharacterInfo.generated.h"

// �÷��̾� ĳ������ ��� ������ ��Ÿ�� �� ���Ǵ� ����ü�Դϴ�.
USTRUCT()
struct UE4RPG_API FPlayerCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public:
	
	// �κ��丮 ���� ����
	UPROPERTY()
	int32 InventorySlotCount;

	// �������� ������
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// ������
	UPROPERTY()
	int32 Silver;

	// ���� �Ӽ�
	UPROPERTY()
	TMap<ECharacterStatusAttribute, float> StatusAttributes;

public :
	FPlayerCharacterInfo();


};
