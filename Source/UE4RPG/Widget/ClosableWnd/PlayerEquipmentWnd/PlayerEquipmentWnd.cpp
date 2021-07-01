#include "PlayerEquipmentWnd.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/Slot/ItemSlot/PlayerEquipSlot/PlayerEquipSlot.h"

void UPlayerEquipmentWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// 장비 아이템 슬롯 위젯 탐색
	{

		// 찾을 슬롯 위젯의 이름을 나타냅니다.
		TArray<FName> equiopSlotNames =
		{
			FName(TEXT("BP_PlayerEquipSlot_Top")),
			FName(TEXT("BP_PlayerEquipSlot_Glove")),
			FName(TEXT("BP_PlayerEquipSlot_Bottom")),
			FName(TEXT("BP_PlayerEquipSlot_Shoes")),
			FName(TEXT("BP_PlayerEquipSlot_Weapon"))
		};

		for (FName slotWidgetName : equiopSlotNames)
		{
			UPlayerEquipSlot* foundEquipSlot = Cast<UPlayerEquipSlot>(GetWidgetFromName(slotWidgetName));
			EquipSlots.Add(foundEquipSlot->GetPartsType(), foundEquipSlot);
		}
	}
	
	// 장비 슬롯 갱신
	UpdatePartsSlots();
}

void UPlayerEquipmentWnd::UpdatePartsSlots()
{
	TMap<EPartsType, FItemSlotInfo>& partsInfo = GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos;

	for (auto equipSlot : EquipSlots)
	{

		// 현재 장착중인 장비 아이템중 equipSlot 과 같은 파츠에 대한 내용을 얻습니다.
		FItemSlotInfo& partsSlotInfo = partsInfo[equipSlot.Key];

		// 내용이 변경되었다면
		if (equipSlot.Value->GetItemInfo()->ItemCode != partsSlotInfo.ItemCode)
			// equipSlot.Key 에 해당하는 파츠를 나타내는 장비 아이템 슬롯 갱신
			equipSlot.Value->UpdateEquipSlot(partsSlotInfo);
	}
}
