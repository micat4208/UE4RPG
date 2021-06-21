#include "BaseSlot.h"


#include "Components/Image.h"
#include "Components/TextBlock.h"

UBaseSlot::UBaseSlot(const FObjectInitializer& objIniter) :
	Super(objIniter)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_SLOT_DRAG_WIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Slot/BP_SlotDragWidget.BP_SlotDragWidget_C'"));
	if (BP_SLOT_DRAG_WIDGET.Succeeded()) BP_SlotDragWidget = BP_SLOT_DRAG_WIDGET.Class;

	bAllowDragOperation = false;
}

void UBaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 개수가 표시되지 않도록 합니다.
	SetSlotItemCount(0);
}

FReply UBaseSlot::NativeOnMouseButtonDown(
	const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	Super::NativeOnMouseButtonDown(inGeometry, inMouseEvent);

	if (inMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		ShowSlotPressedColor();

		// 드래그를 허용하는 슬롯이라면
		if (bAllowDragOperation)
		{
			return UWidgetBlueprintLibrary::DetectDragIfPressed(
				inMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		}


		// 이벤트 처리됨.
		return FReply::Handled();
	}
	// 마우스 오른쪽 버튼이 눌렸다면
	else if (inMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// 마우스 오른쪽 클릭 이벤트 발생
		OnMouseRightButtonClickedEvent.Broadcast();

		// 이벤트 처리됨.
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UBaseSlot::NativeOnMouseButtonUp(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	Super::NativeOnMouseButtonUp(inGeometry, inMouseEvent);

	if (inMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		ShowSlotHoveredColor();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UBaseSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	ShowSlotHoveredColor();

}

void UBaseSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	ShowSlotNormalColor();

}

void UBaseSlot::NativeOnDragDetected(const FGeometry& InGeometry, 
	const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// 드래그 앤 드랍 작업 객체를 생성합니다.
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(
		USlotDragDropOperation::StaticClass());

	USlotDragDropOperation* slotDragDropOp = Cast<USlotDragDropOperation>(OutOperation);
	slotDragDropOp->OriginatedDragSlot = this;

	// 슬롯 드래그 시작 이벤트 발생
	OnSlotDragStarted.Broadcast(slotDragDropOp);
}

bool UBaseSlot::NativeOnDrop(const FGeometry& InGeometry, 
	const FDragDropEvent& InDragDropEvent, 
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	OnSlotDragFinished.Broadcast(Cast<USlotDragDropOperation>(InOperation));

	return false;
}

void UBaseSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	OnSlotDragCancelled.Broadcast(Cast<USlotDragDropOperation>(InOperation));
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

TTuple<UUserWidget*, UImage*> UBaseSlot::CreateSlotDragWidget()
{
	UUserWidget * dragWidget = CreateWidget<UUserWidget>(this, BP_SlotDragWidget);
	UImage* image_Drag = Cast<UImage>(dragWidget->GetWidgetFromName(TEXT("Image_Drag")));

	return MakeTuple(dragWidget, image_Drag);
}

void UBaseSlot::ShowSlotNormalColor()
{
	Image_SlotBackground->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
}

void UBaseSlot::ShowSlotHoveredColor()
{
	Image_SlotBackground->SetColorAndOpacity(FLinearColor(1.0f, 0.46f, 0.0f));
}

void UBaseSlot::ShowSlotPressedColor()
{
	Image_SlotBackground->SetColorAndOpacity(FLinearColor(0.3f, 0.14f, 0.05f));
}
