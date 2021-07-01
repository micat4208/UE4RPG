#include "PlayerEquipSlot.h"

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

void UPlayerEquipSlot::UpdateEquipSlot(FItemSlotInfo& itemSlotInfo)
{
	SetItemInfo(itemSlotInfo.ItemCode);
	UpdateItemImage();
}
