#include "BaseSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 개수가 표시되지 않도록 합니다.
	SetSlotItemCount(0);
}

void UBaseSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	SlotType = slotType;
	InCode = inCode;
}

void UBaseSlot::SetSlotItemCount(int32 itemCount, bool bVisibleBelowOne)
{
	FText countText = FText::FromString(FString::FromInt(itemCount));

	FText itemCountText = (itemCount < 2 && !bVisibleBelowOne) ? FText() : countText;

	Text_Count->SetText(itemCountText);
}
