#include "ItemSlotInfo.h"

FItemSlotInfo::FItemSlotInfo() : FItemSlotInfo(FName()) { }

FItemSlotInfo::FItemSlotInfo(FName itemCode, int32 itemCount, int32 maxSlotCount)
{
	ItemCode = itemCode;
	ItemCount = itemCount;
	MaxSlotCount = maxSlotCount;
}
