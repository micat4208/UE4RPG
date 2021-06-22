#pragma once

#include "UE4RPG.h"
#include "UObject/NoExportTypes.h"

#include "Enum/InputModeType.h"

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
	TSubclassOf<class UInventoryWnd> BP_InventoryWnd;

private :
	class UInventoryWnd* InventoryWnd;

public :
	UPlayerInventory();

public :
	// �κ��丮 â�� �����մϴ�.
	class UInventoryWnd* CreateInventoryWnd(
		class UWidgetController* const widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = false);

	// �κ��丮 â�� �ݽ��ϴ�.
	void CloseInventoryWnd();

	// �κ��丮 â�� ����մϴ�.
	void ToggleInventoryWnd(class UWidgetController* widgetController);

public :
	// �������� �κ��丮�� �߰��մϴ�.
	/// - newItemSlotInfo : �κ��丮�� �߰���ų ������ ������ �����մϴ�.
	void AddItem(FItemSlotInfo& newItemSlotInfo);

	// �������� �κ��丮���� �����մϴ�.
	/// - itemSlotIndex : ������ ������ �ε����� �����մϴ�.
	/// - removeCount : ������ ������ �����մϴ�.
	///   ���� ITEM_ALL �� ���޵ȴٸ� ��� �������� �����մϴ�.
	void RemoveItem(int32 itemSlotIndex, int32 removeCount = ITEM_ALL);

	// �κ��丮 �������� ��ü�մϴ�.
	void SwapItem(class UInventoryItemSlot* first, class UInventoryItemSlot* second);

	// �κ��丮 �������� ��Ĩ�ϴ�.
	void MergeItem(class UInventoryItemSlot* ori, class UInventoryItemSlot* target);

public :
	FORCEINLINE class UInventoryWnd* GetInventoryWnd() const
	{ return InventoryWnd; }
	
};
