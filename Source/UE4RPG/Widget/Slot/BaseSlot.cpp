#include "BaseSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 개수가 표시되지 않도록 합니다.
	SetSlotItemCount(0);
}

FReply UBaseSlot::NativeOnMouseButtonDown(
	const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	// 마우스 오른쪽 버튼이 눌렸다면
	if (inMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// 마우스 오른쪽 클릭 이벤트 발생
		OnMouseRightButtonClickedEvent.Broadcast();

		// 이벤트 처리됨.
		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
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
