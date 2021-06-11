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

public :
	FORCEINLINE class UInventoryWnd* GetInventoryWnd() const
	{ return InventoryWnd; }
	
};
