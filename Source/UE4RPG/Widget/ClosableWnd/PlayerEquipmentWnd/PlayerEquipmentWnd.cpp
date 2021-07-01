#include "PlayerEquipmentWnd.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/Slot/ItemSlot/PlayerEquipSlot/PlayerEquipSlot.h"

void UPlayerEquipmentWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// ��� ������ ���� ���� Ž��
	{

		// ã�� ���� ������ �̸��� ��Ÿ���ϴ�.
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
	
	// ��� ���� ����
	UpdatePartsSlots();
}

void UPlayerEquipmentWnd::UpdatePartsSlots()
{
	TMap<EPartsType, FItemSlotInfo>& partsInfo = GetManager(UPlayerManager)->GetPlayerInfo()->PartsInfos;

	for (auto equipSlot : EquipSlots)
	{

		// ���� �������� ��� �������� equipSlot �� ���� ������ ���� ������ ����ϴ�.
		FItemSlotInfo& partsSlotInfo = partsInfo[equipSlot.Key];

		// ������ ����Ǿ��ٸ�
		if (equipSlot.Value->GetItemInfo()->ItemCode != partsSlotInfo.ItemCode)
			// equipSlot.Key �� �ش��ϴ� ������ ��Ÿ���� ��� ������ ���� ����
			equipSlot.Value->UpdateEquipSlot(partsSlotInfo);
	}
}
