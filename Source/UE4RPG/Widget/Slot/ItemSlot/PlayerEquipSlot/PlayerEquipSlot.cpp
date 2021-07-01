#include "PlayerEquipSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/TextBlock.h"

void UPlayerEquipSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	FString partsText;

	switch (PartsType)
	{
	case EPartsType::PT_Top:
		partsText = TEXT("상의");
		break;
	case EPartsType::PT_Bottom:
		partsText = TEXT("하의");
		break;
	case EPartsType::PT_Glove:
		partsText = TEXT("장갑");
		break;
	case EPartsType::PT_Weapon:
		partsText = TEXT("무기");
		break;
	case EPartsType::PT_Shoes:
		partsText = TEXT("신발");
		break;

	case EPartsType::PT_Hair:
	case EPartsType::PT_Head:
	case EPartsType::PT_LeftGlove:
	case EPartsType::PT_RightGlove:
		break;
	}

	Text_PartsName->SetText(FText::FromString(partsText));
}

void UPlayerEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 우클릭 시 장비 아이템을 장착 해제시킵니다.
	OnMouseRightButtonClickedEvent.AddUObject(this, &UPlayerEquipSlot::DetachToEquipItemSlot);
}

void UPlayerEquipSlot::UpdateEquipSlot(FItemSlotInfo& itemSlotInfo)
{
	SetItemInfo(itemSlotInfo.ItemCode);
	UpdateItemImage();
}

void UPlayerEquipSlot::DetachToEquipItemSlot()
{

	// 슬롯이 비어있다면 실행 X
	if (GetItemInfo()->IsEmpty()) return;

	// 인벤토리 객체
	UPlayerInventory* playerInventory = GetManager(UPlayerManager)->GetPlayerInventory();

	// 전에 장착했던 장비 아이템 정보를 저장시킬 변수
	FItemSlotInfo prevEquippedItemInfo;

	// 장비 아이템 장착 해제[
	playerInventory->DismountItem(PartsType, &prevEquippedItemInfo);

	playerInventory->AddItem(prevEquippedItemInfo);

	UpdateEquipSlot(GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos[PartsType]);
}
