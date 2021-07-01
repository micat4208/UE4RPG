#include "PlayerInventory.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Struct/EquipItemInfo/EquipItemInfo.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"
#include "Widget/ClosableWnd/PlayerEquipmentWnd/PlayerEquipmentWnd.h"
#include "Widget/Slot/ItemSlot/InventoryItemSlot/InventoryItemSlot.h"

#include "Components/CanvasPanelSlot.h"


UPlayerInventory::UPlayerInventory()
{
	static ConstructorHelpers::FClassFinder<UInventoryWnd> BP_INVENTORY_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/InventoryWnd/BP_InventoryWnd.BP_InventoryWnd_C'"));
	if (BP_INVENTORY_WND.Succeeded()) BP_InventoryWnd = BP_INVENTORY_WND.Class;

	static ConstructorHelpers::FClassFinder<UPlayerEquipmentWnd> BP_EQUIP_ITEM_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/EquipItemWnd/BP_EquipItemWnd.BP_EquipItemWnd_C'"));
	if (BP_EQUIP_ITEM_WND.Succeeded()) BP_EquipItemWnd = BP_EQUIP_ITEM_WND.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EQUIP_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_EquipItemInfo.DT_EquipItemInfo'"));
	if (DT_EQUIP_ITEM_INFO.Succeeded()) DT_EquipItemInfo = DT_EQUIP_ITEM_INFO.Object;

	InventoryWnd = nullptr;
	PlayerEquipmentWnd = nullptr;
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

UPlayerEquipmentWnd* UPlayerInventory::CreateEquipmentWnd(UWidgetController* const widgetController, 
	EInputModeType changeInputMode, bool bShowCursor)
{
	if (IsValid(PlayerEquipmentWnd)) return PlayerEquipmentWnd;

	PlayerEquipmentWnd = Cast<UPlayerEquipmentWnd>(
		widgetController->CreateWnd(BP_EquipItemWnd, true, false, changeInputMode, bShowCursor));

	PlayerEquipmentWnd->OnWndClosed.AddLambda([this]()
		{ PlayerEquipmentWnd = nullptr; });

	// �κ��丮 â�� �����ִٸ� �κ��丮 â �������� ��ġ�մϴ�.
	if (IsValid(InventoryWnd))
	{
		FVector2D inventoryHalfSize = InventoryWnd->WndSize * 0.5f;
		FVector2D inventoryWndPos = InventoryWnd->GetCanvasPanelSlot()->GetPosition();

		FVector2D equipmentWndHalfSize = PlayerEquipmentWnd->WndSize * 0.5f;
		FVector2D equipmentWndPos =
			inventoryWndPos + (inventoryHalfSize + equipmentWndHalfSize) * FVector2D(-1.0f, 0.0f);

		equipmentWndPos.Y += equipmentWndHalfSize.Y - inventoryHalfSize.Y;
		PlayerEquipmentWnd->GetCanvasPanelSlot()->SetPosition(equipmentWndPos);
	}

	return PlayerEquipmentWnd;
}

void UPlayerInventory::CloseInventoryWnd()
{
	if (IsValid(InventoryWnd))
		InventoryWnd->CloseThisWnd();
}

void UPlayerInventory::CloseEquipmentWnd()
{
	if (IsValid(PlayerEquipmentWnd))
	{
		PlayerEquipmentWnd->CloseThisWnd();
		PlayerEquipmentWnd = nullptr;
	}
}

void UPlayerInventory::ToggleInventoryWnd(UWidgetController* widgetController, bool bOpenEquipmentWnd)
{
	if (IsValid(InventoryWnd))
	{
		CloseInventoryWnd();
		CloseEquipmentWnd();
	}
	else
	{
		CreateInventoryWnd(widgetController, EInputModeType::IM_GameAndUI, true);

		if (bOpenEquipmentWnd)
			CreateEquipmentWnd(widgetController, EInputModeType::IM_GameAndUI, true);
	}
}

void UPlayerInventory::UpdateCharacterVisual()
{
	// ���� ������ ��� ���� Ÿ���� ����ϴ�.
	TArray<EPartsType> equipItemPartsTypes;
	GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos.GetKeys(equipItemPartsTypes);
	/// - TMap.GetKeys(&TArray<KeyType> outKeys) : TMap ����� ��� Ű�� �迭�� ��ȯ�մϴ�.
	/// - outKeys : ��¿� �Ű� �����̸�, TMap ��ҵ��� Ű�� �����ų �迭�� �����մϴ�.
	
	// ��� ���� ������� �����մϴ�.
	for (EPartsType partsType : equipItemPartsTypes)
	{
		UpdateCharacterVisual(partsType);
	}
}

void UPlayerInventory::UpdateCharacterVisual(EPartsType updateParts)
{
	// �÷��̾� ĳ���Ͱ� ��ȿ���� ���� ��� ����
	APlayerCharacter* playerCharacter = GetManager(UPlayerManager)->GetPlayerCharacter();
	if (!IsValid(playerCharacter)) return;

	// �÷��̾� ĳ���� ������ ����ϴ�.
	FPlayerCharacterInfo* playerCharacterInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	// ���� ������ ������ updateParts �� ��ġ�ϴ� ���� ������ ����ϴ�.
	bool bReturnedAvilableData = false; // ��ȯ�� �����Ͱ� ��ȿ�� ���������� Ȯ���ϱ� ���� ����
	TTuple<FItemSlotInfo, bool> equippedPartsData = playerCharacterInfo->GetEquippedItemSlotInfo(
		updateParts, &bReturnedAvilableData);

	// ��ȿ�� �����Ͱ� �ƴ϶�� return
	if (!bReturnedAvilableData) return;

	// ���� ������ ��� ������ ����
	FItemSlotInfo* equippedItemSlotInfo = &equippedPartsData.Get<0>();

	// ������ ��� �������� �⺻ ������� ��Ÿ���ϴ�.
	bool bIsDefaultEquipItem = equippedPartsData.Get<1>();

	// ��ȿ�� �������̳� ������ ������� ��� ����
	if (equippedItemSlotInfo->IsEmpty()) return;

	// ��� ������ ������ ����ϴ�.
	FString contextString;
	FEquipItemInfo * equipItemInfo = DT_EquipItemInfo->FindRow<FEquipItemInfo>(
		equippedItemSlotInfo->ItemCode,
		contextString);

	USkeletalMesh* loadedMesh = Cast<USkeletalMesh>(
			GetManager(FStreamableManager)->LoadSynchronous(equipItemInfo->MeshPath));

	USkeletalMesh* loadedSetMesh = nullptr;
	if (!equipItemInfo->SetMeshPath.IsNull())
	{
		loadedSetMesh = Cast<USkeletalMesh>(
			GetManager(FStreamableManager)->LoadSynchronous(equipItemInfo->SetMeshPath));
	}


	switch (equipItemInfo->PartsType)
	{
	case EPartsType::PT_Hair:
	case EPartsType::PT_Head:
	case EPartsType::PT_Top:
	case EPartsType::PT_Bottom:
	case EPartsType::PT_Shoes:
	case EPartsType::PT_Weapon:
		playerCharacter->GetParts()[equipItemInfo->PartsType]->SetSkeletalMesh(loadedMesh);
		break;

	case EPartsType::PT_Glove:
		playerCharacter->GetParts()[EPartsType::PT_LeftGlove]->SetSkeletalMesh(loadedMesh);
		playerCharacter->GetParts()[EPartsType::PT_RightGlove]->SetSkeletalMesh(loadedSetMesh);
		break;
	}

	if (equipItemInfo->PartsType == EPartsType::PT_Glove)
	{
		playerCharacter->GetParts()[EPartsType::PT_LeftGlove]->SetRelativeLocation(equipItemInfo->RelativeLocation);
		playerCharacter->GetParts()[EPartsType::PT_RightGlove]->SetRelativeLocation(equipItemInfo->RelativeLocation);
	}
	else
	{
		// ��� ��ġ ����
		playerCharacter->GetParts()[equipItemInfo->PartsType]->SetRelativeLocation(equipItemInfo->RelativeLocation);
	}

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

void UPlayerInventory::EquipItem(FName equipItemCode)
{
	// ��� ������ ������ ����ϴ�.
	FString contextString;
	FEquipItemInfo* equipItemInfo = DT_EquipItemInfo->FindRow<FEquipItemInfo>(
		equipItemCode, contextString);

	if (equipItemCode.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInventory.cpp :: %d LINE :: equipItemCode is None!"), __LINE__);
		return;
	}
	else if (equipItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInventory.cpp :: %d LINE :: equipItemInfo is nullptr! (equipItemCode = %s) "),
			__LINE__, *equipItemCode.ToString());
		return;
	}

	// ��� ������ ����
	GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos[equipItemInfo->PartsType] =
		FItemSlotInfo(equipItemCode, 1, 1);

	// ����� ����
	UpdateCharacterVisual(equipItemInfo->PartsType);
}