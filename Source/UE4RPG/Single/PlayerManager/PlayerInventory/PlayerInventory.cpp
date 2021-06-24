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
		widgetController->CreateWnd(BP_InventoryWnd, true, false, changeInputMode, bShowCursor));

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

	Func(UpdateInventorySlots, (TArray<UInventoryItemSlot*>& _changedInventoryItemSlots),
		&inventoryItemInfos)
	{
		for (int32 i = 0; i < _changedInventoryItemSlots.Num(); ++i)
		{
			UInventoryItemSlot* changedInventoryItemSlot = _changedInventoryItemSlots[i];

			changedInventoryItemSlot->SetItemInfo(
				inventoryItemInfos[i].ItemCode);

			changedInventoryItemSlot->UpdateInventoryItemSlot();
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

		// ��� �������� �߰��� ���
		if (newItemSlotInfo.ItemCount <= 0)
		{
			// ������ ����� ���Ե� ����
			UpdateInventorySlots(changedInventoryItemSlots);

			// ��� ������ �߰���
			return;
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

void UPlayerInventory::SwapItem(class UInventoryItemSlot* first, class UInventoryItemSlot* second)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	TArray<FItemSlotInfo>& inventoryItemInfos = playerInfo->InventoryItemInfos;

	FItemSlotInfo tempItemInfo = inventoryItemInfos[first->GetItemSlotIndex()];
	inventoryItemInfos[first->GetItemSlotIndex()] = inventoryItemInfos[second->GetItemSlotIndex()];
	inventoryItemInfos[second->GetItemSlotIndex()] = tempItemInfo;

	first->SetItemInfo(inventoryItemInfos[first->GetItemSlotIndex()].ItemCode);
	second->SetItemInfo(inventoryItemInfos[second->GetItemSlotIndex()].ItemCode);
	first->UpdateInventoryItemSlot();
	second->UpdateInventoryItemSlot();
}

void UPlayerInventory::MergeItem(UInventoryItemSlot* ori, UInventoryItemSlot* target)
{
	FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	FItemSlotInfo& oriItemSlotInfo = playerInfo->InventoryItemInfos[ori->GetItemSlotIndex()];
	FItemSlotInfo& targetItemSlotInfo = playerInfo->InventoryItemInfos[target->GetItemSlotIndex()];

	// ���Կ� �� �� �մ� �ִ� ������ ����
	int32 maxSlotCount = ori->GetItemInfo()->MaxSlotCount;

	// ori �� target �� �� �ϳ��� �ִ� ������� ������ �Ͼ���� �մϴ�.
	if (oriItemSlotInfo.ItemCount == maxSlotCount ||
		targetItemSlotInfo.ItemCount == maxSlotCount)
		Swap(ori, target);

	// ä�� �� �ִ� ������ �����Ѵٸ�
	else
	{
		// �߰� ������ ������ ������ ����մϴ�.
		int32 addable = maxSlotCount - targetItemSlotInfo.ItemCount;

		// �߰� ������ �������� ������ Ŭ ���
		if (addable > oriItemSlotInfo.ItemCount)
			addable = oriItemSlotInfo.ItemCount;

		// �������� �ű�ϴ�.
		oriItemSlotInfo.ItemCount -= addable;
		targetItemSlotInfo.ItemCount += addable;

		// �ű� �� ������ ����ִٸ�
		if (oriItemSlotInfo.ItemCount == 0)
		{
			oriItemSlotInfo.Clear();
			ori->SetItemInfo(FName());
		}

		// ���� ����
		ori->UpdateInventoryItemSlot();
		target->UpdateInventoryItemSlot();
	}
}

void UPlayerInventory::RemoveItem(int32 itemSlotIndex, int32 removeCount)
{
	FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	UInventoryWnd * inventoryWnd = GetInventoryWnd();
	TArray<FItemSlotInfo>& inventoryItemInfos = playerInfo->InventoryItemInfos;

	// removeCount �� ITEM_ALL �� ���޵Ǿ��ٸ� ������ ������ ���ϴ�.
	inventoryItemInfos[itemSlotIndex].ItemCount -=
		(removeCount == ITEM_ALL) ?
		inventoryItemInfos[itemSlotIndex].ItemCount :
		removeCount;

	// itemSlotIndex ���� ���Կ� �������� �������� ���� ���
	if (inventoryItemInfos[itemSlotIndex].ItemCount <= 0)

		// ���� ������ ���ϴ�.
		inventoryItemInfos[itemSlotIndex].Clear();

	// �κ��丮 â�� ���� ��� ���� ����
	if (IsValid(inventoryWnd))
		inventoryWnd->GetItemSlots()[itemSlotIndex]->UpdateInventoryItemSlot();



}
