#pragma once

#include "CoreMinimal.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "Enum/CharacterStatusAttribute.h"
#include "Enum/PartsType.h"

#include "PlayerCharacterInfo.generated.h"

// 플레이어의 상태 속성이 변경되었을 경우 호출되는 대리자 형식
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnStatusAttributesChanged, ECharacterStatusAttribute, float, float)
/// - Param1 : 변경된 상태 속성 타입
/// - Param2 : 변경 전 수치
/// - Param3 : 변경된 수치

// 플레이어 캐릭터의 기반 정보를 나타낼 때 사용되는 구조체입니다.
USTRUCT()
struct UE4RPG_API FPlayerCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public :
	// 플레이어의 상태 속성 수치가 변경되었을 경우 호출되는 대리자입니다.
	FOnStatusAttributesChanged OnStatusAttributesChanged;

public:
	
	// 인벤토리 슬롯 개수
	UPROPERTY()
	int32 InventorySlotCount;

	// 소지중인 아이템
	UPROPERTY()
	TArray<FItemSlotInfo> InventoryItemInfos;

	// 기본 장착 아이템 정보
	UPROPERTY()
	TMap<EPartsType, FItemSlotInfo> DefaultPartsInfos;

	// 장착 아이템 정보
	UPROPERTY()
	TMap<EPartsType, FItemSlotInfo> PartsInfos;

	// 소지금
	UPROPERTY()
	int32 Silver;

	// 상태 속성
	UPROPERTY()
	TMap<ECharacterStatusAttribute, float> StatusAttributes;

public :
	FPlayerCharacterInfo();

	// statusAttributes 에 해당하는 상태 속성의 수치를 value 로 설정합니다.
	void SetStatusAttributes(ECharacterStatusAttribute statusAttributes, float value);

	// statusAttributes 에 해당하는 상태 속성의 수치에 value 를 더합니다.
	void AddStatusAttributes(ECharacterStatusAttribute statusAttributes, float value);

	// 현재 장착한 장비 아이템 정보를 얻습니다.
	/// - 착용중인 장비 아이템이 존재한다면 착용중인 장비 아이템 정보가 반환되며,
	///   착용중인 장비 아이템이 존재하지 않는다면 기본 아이템 정보가 반환됩니다.
	/// - return : <장비 아이템 슬롯 정보, 반환된 아이템 정보가 기본 장비 아이템 정보임>
	TTuple<FItemSlotInfo, bool> GetEquippedItemSlotInfo(EPartsType partsType, bool * out_bReturnedAvilableData = nullptr) const;


};
