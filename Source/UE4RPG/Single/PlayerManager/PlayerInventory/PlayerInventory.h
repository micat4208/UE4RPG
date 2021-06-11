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
	// 인벤토리 창을 생성합니다.
	class UInventoryWnd* CreateInventoryWnd(
		class UWidgetController* const widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = false);

	// 인벤토리 창을 닫습니다.
	void CloseInventoryWnd();

	// 인벤토리 창을 토글합니다.
	void ToggleInventoryWnd(class UWidgetController* widgetController);

public :
	// 아이템을 인벤토리에 추가합니다.
	/// - newItemSlotInfo : 인벤토리에 추가시킬 아이템 정보를 전달합니다.
	void AddItem(FItemSlotInfo& newItemSlotInfo);

public :
	FORCEINLINE class UInventoryWnd* GetInventoryWnd() const
	{ return InventoryWnd; }
	
};
