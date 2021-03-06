#pragma once

#include "UE4RPG.h"
#include "UObject/NoExportTypes.h"

#include "Enum/InputModeType.h"
#include "Enum/PartsType.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "PlayerInventory.generated.h"

UCLASS()
class UE4RPG_API UPlayerInventory final : 
	public UObject
{
	GENERATED_BODY()

public :
	enum EItemCount : int8{ ITEM_ALL = -1 };

private :
	TSubclassOf<class UPlayerEquipmentWnd> BP_EquipItemWnd;
	TSubclassOf<class UInventoryWnd> BP_InventoryWnd;
	class UDataTable* DT_EquipItemInfo;

private :
	class UInventoryWnd* InventoryWnd;
	class UPlayerEquipmentWnd* PlayerEquipmentWnd;

public :
	UPlayerInventory();

public :
	// 인벤토리 창을 생성합니다.
	class UInventoryWnd* CreateInventoryWnd(
		class UWidgetController* const widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = false);

	// 장비 아이템 창을 생성합니다.
	class UPlayerEquipmentWnd* CreateEquipmentWnd(
		class UWidgetController* const widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = false);

	// 인벤토리 창을 닫습니다.
	void CloseInventoryWnd();

	// 장비 아이템 창을 닫습니다.
	void CloseEquipmentWnd();

	// 인벤토리 창을 토글합니다.
	void ToggleInventoryWnd(class UWidgetController* widgetController, bool bOpenEquipmentWnd = false);

public :
	// 플레이어 캐릭터의 비쥬얼을 갱신합니다.
	void UpdateCharacterVisual();

	// 플레이어 캐릭터의 비쥬얼을 갱신합니다.
	void UpdateCharacterVisual(EPartsType updateParts);

public :
	// 아이템을 인벤토리에 추가합니다.
	/// - newItemSlotInfo : 인벤토리에 추가시킬 아이템 정보를 전달합니다.
	void AddItem(FItemSlotInfo& newItemSlotInfo);

	// 아이템을 인벤토리에서 제거합니다.
	/// - itemSlotIndex : 제거할 슬롯의 인덱스를 전달합니다.
	/// - removeCount : 제거할 개수를 전달합니다.
	///   만약 ITEM_ALL 이 전달된다면 모든 아이템을 제거합니다.
	void RemoveItem(int32 itemSlotIndex, int32 removeCount = ITEM_ALL);

	// 인벤토리 아이템을 교체합니다.
	void SwapItem(class UInventoryItemSlot* first, class UInventoryItemSlot* second);

	// 인벤토리 아이템을 합칩니다.
	void MergeItem(class UInventoryItemSlot* ori, class UInventoryItemSlot* target);

	// 장비 아이템을 장착합니다.
	void EquipItem(FName equipItemCode);

	// 장비 아이템을 장착 해제시킵니다.
	// partsType : 장착 해제시키려는 파츠를 전달합니다.
	// out_ItemSlotInfo : 이전에 장착시킨 아이템 정보를 전달받을 ItemSlotInfo 를 나타냅니다.
	void DismountItem(EPartsType partsType, FItemSlotInfo* out_ItemSlotInfo = nullptr);

public :
	FORCEINLINE class UInventoryWnd* GetInventoryWnd() const
	{ return InventoryWnd; }

	FORCEINLINE class UPlayerEquipmentWnd* GetPlayerEquipmentWnd() const
	{ return PlayerEquipmentWnd; }

	// 무기 장착 상태를 반환합니다.
	bool IsEquippedWeapon() const;
	
};
