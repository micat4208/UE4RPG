#include "InventoryItemSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjIniter) :
	Super(ObjIniter)
{
	// 이 슬롯에서 드래깅 작업을 허용합니다.
	bAllowDragOperation = true;
}

void UInventoryItemSlot::InitializeSlot(ESlotType slotType, FName itemCode, int32 itemSlotIndex)
{
	Super::InitializeSlot(slotType, itemCode);

	ItemSlotIndex = itemSlotIndex;

	UpdateItemCountText();
}

void UInventoryItemSlot::UpdateInventoryItemSlot()
{
	SetItemInfo(GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[ItemSlotIndex].ItemCode);
	UpdateItemImage();
	UpdateItemCountText();
}

void UInventoryItemSlot::UpdateItemCountText()
{
	auto& itemSlotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->
		InventoryItemInfos[ItemSlotIndex];

	SetSlotItemCount(itemSlotInfo.ItemCount);
}
