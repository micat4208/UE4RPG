#include "BaseSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBaseSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	SlotType = slotType;
	InCode = inCode;
}
