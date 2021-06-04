#include "InventoryWnd.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/Slot/ItemSlot/InventoryItemSlot/InventoryItemSlot.h"
#include "Widget/WidgetController/WidgetController.h"

#include "Components/GridPanel.h"



UInventoryWnd::UInventoryWnd(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventoryItemSlot> BP_INVENTORY_ITEM_SLOT(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Slot/BP_InventoryItemSlot.BP_InventoryItemSlot_C'"));
	if (BP_INVENTORY_ITEM_SLOT.Succeeded()) BP_InventoryItemSlot = BP_INVENTORY_ITEM_SLOT.Class;

}

void UInventoryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(460.0f, 700.0f);

	InitializeInventoryWnd();
}

void UInventoryWnd::InitializeInventoryWnd()
{
	const int32 maxColumnCount = 6;
	int32 currentColumnCount = 0;

	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	int32 inventorySlotCount = playerInfo->InventorySlotCount;

	for (int32 i = 0; i < inventorySlotCount; ++i)
	{
		auto newItemSlot = CreateItemSlot();
		newItemSlot->InitializeSlot(
			ESlotType::InventorySlot,
			playerInfo->InventoryItemInfos[i].ItemCode, i);

		UWidgetController::SortGridPanelElem(
			newItemSlot, maxColumnCount, currentColumnCount);
	}

}

UInventoryItemSlot* UInventoryWnd::CreateItemSlot()
{
	UInventoryItemSlot* newItemSlot = CreateWidget<UInventoryItemSlot>(this, BP_InventoryItemSlot);
	GridPanel_ItemSlots->AddChild(newItemSlot);

	ItemSlots.Add(newItemSlot);

	return newItemSlot;
}
