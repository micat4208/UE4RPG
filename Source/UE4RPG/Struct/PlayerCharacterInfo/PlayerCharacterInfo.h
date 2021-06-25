#pragma once

#include "CoreMinimal.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "Enum/CharacterStatusAttribute.h"
#include "Enum/PartsType.h"

#include "PlayerCharacterInfo.generated.h"

// �÷��̾��� ���� �Ӽ��� ����Ǿ��� ��� ȣ��Ǵ� �븮�� ����
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnStatusAttributesChanged, ECharacterStatusAttribute, float, float)
/// - Param1 : ����� ���� �Ӽ� Ÿ��
/// - Param2 : ���� �� ��ġ
/// - Param3 : ����� ��ġ

// �÷��̾� ĳ������ ��� ������ ��Ÿ�� �� ���Ǵ� ����ü�Դϴ�.
USTRUCT()
struct UE4RPG_API FPlayerCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public :
	// �÷��̾��� ���� �Ӽ� ��ġ�� ����Ǿ��� ��� ȣ��Ǵ� �븮���Դϴ�.
	FOnStatusAttributesChanged OnStatusAttributesChanged;

public:
	
	// �κ��丮 ���� ����
	UPROPERTY()
	int32 InventorySlotCount;

	// �������� ������
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// �⺻ ���� ������ ����
	UPROPERTY()
	TMap<EPartsType, FItemSlotInfo> DefaultPartsInfos;

	// ���� ������ ����
	UPROPERTY()
	TMap<EPartsType, FItemSlotInfo> PartsInfos;

	// ������
	UPROPERTY()
	int32 Silver;

	// ���� �Ӽ�
	UPROPERTY()
	TMap<ECharacterStatusAttribute, float> StatusAttributes;

public :
	FPlayerCharacterInfo();

	// statusAttributes �� �ش��ϴ� ���� �Ӽ��� ��ġ�� value �� �����մϴ�.
	void SetStatusAttributes(ECharacterStatusAttribute statusAttributes, float value);

	// statusAttributes �� �ش��ϴ� ���� �Ӽ��� ��ġ�� value �� ���մϴ�.
	void AddStatusAttributes(ECharacterStatusAttribute statusAttributes, float value);


};
