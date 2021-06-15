#include "PlayerCharacterInfo.h"


FPlayerCharacterInfo::FPlayerCharacterInfo()
{
	InventorySlotCount = 30;

	// Test Code ...
	Silver = 100000;

	for (int32 i = 0; i < InventorySlotCount; ++i)
		InventoryItemInfos.Add(FItemSlotInfo());

	InventoryItemInfos[0] = (FItemSlotInfo(FName(TEXT("90009")), 3, 100));
}