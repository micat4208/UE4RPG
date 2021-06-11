#include "PlayerInventory.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"
#include "Widget/Slot/ItemSlot/InventoryItemSlot/InventoryItemSlot.h"


UPlayerInventory::UPlayerInventory()
{
	static ConstructorHelpers::FClassFinder<UInventoryWnd> BP_INVENTORY_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/InventoryWnd/BP_InventoryWnd.BP_InventoryWnd_C'"));
	if (BP_INVENTORY_WND.Succeeded()) BP_InventoryWnd = BP_INVENTORY_WND.Class;

	InventoryWnd = nullptr;
}

UInventoryWnd* UPlayerInventory::CreateInventoryWnd(
	UWidgetController* const	widgetController,
	EInputModeType				changeInputMode, 
	bool						bShowCursor)
{
	if (IsValid(InventoryWnd)) return InventoryWnd;

	// â�� ���ϴ�.
	InventoryWnd = Cast<UInventoryWnd>(
		widgetController->CreateWnd(BP_InventoryWnd, true, changeInputMode, bShowCursor));

	// â�� ���� �� InventoryWnd �� nullptr �� �ɼ� �ֵ��� �մϴ�.
	InventoryWnd->OnWndClosed.AddLambda(
		[this]() { InventoryWnd = nullptr; });

	// ������ InventoryWnd �� ��ȯ�ϵ��� �մϴ�.
	return InventoryWnd;
}

void UPlayerInventory::CloseInventoryWnd()
{
	if (IsValid(InventoryWnd))
		InventoryWnd->CloseThisWnd();
}

void UPlayerInventory::ToggleInventoryWnd(UWidgetController* widgetController)
{
	if (IsValid(InventoryWnd)) CloseInventoryWnd();
	else CreateInventoryWnd(widgetController, EInputModeType::IM_GameAndUI, true);
}

void UPlayerInventory::AddItem(FItemSlotInfo& newItemSlotInfo)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	TArray<FItemSlotInfo>& inventoryItemInfos = playerInfo->InventoryItemInfos;

	// index �� �ش��ϴ� ���Կ� �Ű����� newItemSlotInfo �� ������ �������� �ִ��� ä��� �Լ��Դϴ�.
	Func(FillSlot, (int32 index), 
		&newItemSlotInfo, &inventoryItemInfos)
	{
		// �������� �߰��� �� �ִ� ���� ������ �����ϴ��� Ȯ���մϴ�.
		/// - �ִ� ������ ���� - ���� �������� ������ ���� = �߰� ������ ����
		int32 addableItemCount = inventoryItemInfos[index].MaxSlotCount -
			inventoryItemInfos[index].ItemCount;

		// index ��° ���Կ� �������� �߰��� �� �ִٸ�
		if (addableItemCount > 0)
		{
			// �߰��� �� �ִ� ������ ������ ���մϴ�.
			addableItemCount =
				(addableItemCount < newItemSlotInfo.ItemCount) ?
				addableItemCount :
				newItemSlotInfo.ItemCount;

			// �������� ä��ϴ�.
			inventoryItemInfos[index].ItemCount += addableItemCount;

			// �߰��� �������� �����մϴ�.
			newItemSlotInfo.ItemCount -= addableItemCount;
		}
	};



	// ������ ����� �κ��丮 ���Ե��� ������ �迭
	TArray<UInventoryItemSlot*> changedInventoryItemSlots;

	for (int32 i = 0; i < playerInfo->InventorySlotCount; ++i)
	{

		// ���� �߰��Ϸ��� �����۰� ������ �������� ���� ������ ã�Ҵٸ�
		if (inventoryItemInfos[i].IsSameItem(newItemSlotInfo))
		{
			// �ش� ����(inventoryItemInfos[i])�� �������� �ִ��� ä��ϴ�.
			FillSlot(i);

			// ������ �����Ų �κ��丮 ������ �迭�� �߰��մϴ�.
			if (IsValid(InventoryWnd))
				changedInventoryItemSlots.Add(InventoryWnd->GetItemSlots()[i]);
		}

		// �� ������ ������ ã�Ҵٸ�
		else if (inventoryItemInfos[i].IsEmpty())
		{
			// �߰���Ű���� ������ ItemCode, MaxSlotCount �� ���� �߰��Ϸ��� �������� �������� �����մϴ�.
			inventoryItemInfos[i] = newItemSlotInfo;
			inventoryItemInfos[i].ItemCount = 0;

			// �������� ä��ϴ�.
			FillSlot(i);

			// ������ �����Ų �κ��丮 ������ �迭�� �߰��մϴ�.
			if (IsValid(InventoryWnd))
				changedInventoryItemSlots.Add(InventoryWnd->GetItemSlots()[i]);
		}
	}

	// �κ��丮 â�� ���� ��� ���Ž�ŵ�ϴ�.
	/// - ������ ����� �κ��丮 ���Ե��� ���Ž�ŵ�ϴ�.
	for (int32 i = 0; i < changedInventoryItemSlots.Num(); ++i)
	{
		UInventoryItemSlot* changedInventoryItemSlot = changedInventoryItemSlots[i];

		changedInventoryItemSlot->SetItemInfo(
			inventoryItemInfos[i].ItemCode);

		changedInventoryItemSlot->UpdateInventoryItemSlot();
	}
}
