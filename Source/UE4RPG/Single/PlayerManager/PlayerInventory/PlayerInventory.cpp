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

	// 창을 띄웁니다.
	InventoryWnd = Cast<UInventoryWnd>(
		widgetController->CreateWnd(BP_InventoryWnd, true, false, changeInputMode, bShowCursor));

	// 창이 닫힐 때 InventoryWnd 가 nullptr 가 될수 있도록 합니다.
	InventoryWnd->OnWndClosed.AddLambda(
		[this]() { InventoryWnd = nullptr; });

	// 생성된 InventoryWnd 를 반환하도록 합니다.
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

	// 인벤토리 창이 열려있다면 인벤토리 창 우측으로 배치합니다.
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
	// 장착 가능한 모든 파츠 타입을 얻습니다.
	TArray<EPartsType> equipItemPartsTypes;
	GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos.GetKeys(equipItemPartsTypes);
	/// - TMap.GetKeys(&TArray<KeyType> outKeys) : TMap 요소의 모든 키를 배열로 반환합니다.
	/// - outKeys : 출력용 매개 변수이며, TMap 요소들의 키를 저장시킬 배열을 전달합니다.
	
	// 모든 파츠 비쥬얼을 갱신합니다.
	for (EPartsType partsType : equipItemPartsTypes)
	{
		UpdateCharacterVisual(partsType);
	}
}

void UPlayerInventory::UpdateCharacterVisual(EPartsType updateParts)
{
	// 플레이어 캐릭터가 유효하지 않을 경우 리턴
	APlayerCharacter* playerCharacter = GetManager(UPlayerManager)->GetPlayerCharacter();
	if (!IsValid(playerCharacter)) return;

	// 플레이어 캐릭터 정보를 얻습니다.
	FPlayerCharacterInfo* playerCharacterInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	// 현재 장착된 파츠중 updateParts 와 일치하는 파츠 정보를 얻습니다.
	bool bReturnedAvilableData = false; // 반환된 데이터가 유효한 데이터임을 확인하기 위한 변수
	TTuple<FItemSlotInfo, bool> equippedPartsData = playerCharacterInfo->GetEquippedItemSlotInfo(
		updateParts, &bReturnedAvilableData);

	// 유효한 데이터가 아니라면 return
	if (!bReturnedAvilableData) return;

	// 현재 장착된 장비 아이템 정보
	FItemSlotInfo* equippedItemSlotInfo = &equippedPartsData.Get<0>();

	// 장착된 장비 아이템이 기본 장비임을 나타냅니다.
	bool bIsDefaultEquipItem = equippedPartsData.Get<1>();

	// 유효한 데이터이나 정보가 비어있을 경우 리턴
	if (equippedItemSlotInfo->IsEmpty()) return;

	// 장비 아이템 정보를 얻습니다.
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
		// 상대 위치 설정
		playerCharacter->GetParts()[equipItemInfo->PartsType]->SetRelativeLocation(equipItemInfo->RelativeLocation);
	}

}

void UPlayerInventory::AddItem(FItemSlotInfo& newItemSlotInfo)
{
	auto playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	TArray<FItemSlotInfo>& inventoryItemInfos = playerInfo->InventoryItemInfos;

	// index 에 해당하는 슬롯에 매개변수 newItemSlotInfo 에 전달한 아이템을 최대한 채우는 함수입니다.
	Func(FillSlot, (int32 index), 
		&newItemSlotInfo, &inventoryItemInfos)
	{
		// 아이템을 추가할 수 있는 여유 공간이 존재하는지 확인합니다.
		/// - 최대 아이템 개수 - 현재 소지중인 아이템 개수 = 추가 가능한 개수
		int32 addableItemCount = inventoryItemInfos[index].MaxSlotCount -
			inventoryItemInfos[index].ItemCount;

		// index 번째 슬롯에 아이템을 추가할 수 있다면
		if (addableItemCount > 0)
		{
			// 추가할 수 있는 아이템 개수를 구합니다.
			addableItemCount =
				(addableItemCount < newItemSlotInfo.ItemCount) ?
				addableItemCount :
				newItemSlotInfo.ItemCount;

			// 아이템을 채웁니다.
			inventoryItemInfos[index].ItemCount += addableItemCount;

			// 추가한 아이템을 제외합니다.
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


	// 내용이 변경된 인벤토리 슬롯들을 저장할 배열
	TArray<UInventoryItemSlot*> changedInventoryItemSlots;

	for (int32 i = 0; i < playerInfo->InventorySlotCount; ++i)
	{

		// 만약 추가하려는 아이템과 동일한 아이템을 갖는 슬롯을 찾았다면
		if (inventoryItemInfos[i].IsSameItem(newItemSlotInfo))
		{
			// 해당 슬롯(inventoryItemInfos[i])에 아이템을 최대한 채웁니다.
			FillSlot(i);

			// 내용을 변경시킨 인벤토리 슬롯을 배열에 추가합니다.
			if (IsValid(InventoryWnd))
				changedInventoryItemSlots.Add(InventoryWnd->GetItemSlots()[i]);
		}

		// 빈 아이템 슬롯을 찾았다면
		else if (inventoryItemInfos[i].IsEmpty())
		{
			// 추가시키려는 슬롯의 ItemCode, MaxSlotCount 의 값을 추가하려는 아이템의 내용으로 설정합니다.
			inventoryItemInfos[i] = newItemSlotInfo;
			inventoryItemInfos[i].ItemCount = 0;

			// 아이템을 채웁니다.
			FillSlot(i);

			// 내용을 변경시킨 인벤토리 슬롯을 배열에 추가합니다.
			if (IsValid(InventoryWnd))
				changedInventoryItemSlots.Add(InventoryWnd->GetItemSlots()[i]);
		}

		// 모든 아이템을 추가한 경우
		if (newItemSlotInfo.ItemCount <= 0)
		{
			// 내용이 변경된 슬롯들 갱신
			UpdateInventorySlots(changedInventoryItemSlots);

			// 모든 아이템 추가함
			return;
		}
	}

	// 인벤토리 창이 열린 경우 갱신시킵니다.
	/// - 내용이 변경된 인벤토리 슬롯들을 갱신시킵니다.
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

	// 슬롯에 들어갈 수 잇는 최대 아이템 개수
	int32 maxSlotCount = ori->GetItemInfo()->MaxSlotCount;

	// ori 나 target 둘 중 하나라도 최대 개수라면 스왑이 일어나도록 합니다.
	if (oriItemSlotInfo.ItemCount == maxSlotCount ||
		targetItemSlotInfo.ItemCount == maxSlotCount)
		Swap(ori, target);

	// 채울 수 있는 공간이 존재한다면
	else
	{
		// 추가 가능한 아이템 개수를 계산합니다.
		int32 addable = maxSlotCount - targetItemSlotInfo.ItemCount;

		// 추가 가능한 아이템의 개수가 클 경우
		if (addable > oriItemSlotInfo.ItemCount)
			addable = oriItemSlotInfo.ItemCount;

		// 아이템을 옮깁니다.
		oriItemSlotInfo.ItemCount -= addable;
		targetItemSlotInfo.ItemCount += addable;

		// 옮긴 후 슬롯이 비어있다면
		if (oriItemSlotInfo.ItemCount == 0)
		{
			oriItemSlotInfo.Clear();
			ori->SetItemInfo(FName());
		}

		// 슬롯 갱신
		ori->UpdateInventoryItemSlot();
		target->UpdateInventoryItemSlot();
	}
}

void UPlayerInventory::RemoveItem(int32 itemSlotIndex, int32 removeCount)
{
	FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	UInventoryWnd * inventoryWnd = GetInventoryWnd();
	TArray<FItemSlotInfo>& inventoryItemInfos = playerInfo->InventoryItemInfos;

	// removeCount 에 ITEM_ALL 이 전달되었다면 슬롯을 완전히 비웁니다.
	inventoryItemInfos[itemSlotIndex].ItemCount -=
		(removeCount == ITEM_ALL) ?
		inventoryItemInfos[itemSlotIndex].ItemCount :
		removeCount;

	// itemSlotIndex 번재 슬롯에 아이템이 존재하지 않을 경우
	if (inventoryItemInfos[itemSlotIndex].ItemCount <= 0)

		// 슬롯 정보를 비웁니다.
		inventoryItemInfos[itemSlotIndex].Clear();

	// 인벤토리 창이 열린 경우 슬롯 갱신
	if (IsValid(inventoryWnd))
		inventoryWnd->GetItemSlots()[itemSlotIndex]->UpdateInventoryItemSlot();



}

void UPlayerInventory::EquipItem(FName equipItemCode)
{
	// 장비 아이템 정보를 얻습니다.
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

	// 장비 아이템 장착
	GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos[equipItemInfo->PartsType] =
		FItemSlotInfo(equipItemCode, 1, 1);

	// 비쥬얼 갱신
	UpdateCharacterVisual(equipItemInfo->PartsType);
}