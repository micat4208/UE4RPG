#include "DraggableWndTitle.h"

#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

#include "Blueprint/WidgetLayoutLibrary.h"

UDraggableWndTitle::UDraggableWndTitle(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	bIsDragging = false;
	TargetWnd = nullptr;
}

void UDraggableWndTitle::NativePreConstruct()
{
	Super::NativePreConstruct();

	Text_Title->SetText(TitleText);
}

void UDraggableWndTitle::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Draggable->OnPressed.AddDynamic(this, &UDraggableWndTitle::OnWidgetDragStarted);
	Button_Draggable->OnReleased.AddDynamic(this, &UDraggableWndTitle::OnWidgetDragFinished);
}

void UDraggableWndTitle::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (TargetWnd && bIsDragging) DragWidget();
}

void UDraggableWndTitle::DragWidget()
{
	// 마우스 위치를 얻습니다.
	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	/// - UWidgetLayoutLibrary : 위젯 레이아웃과 관련된 유틸성 정적 메서드들을 제공하는 클래스

	// 드래그 이동시킬 창 위젯의 슬롯을 얻습니다.
	UCanvasPanelSlot* targetSlot = Cast<UCanvasPanelSlot>(TargetWnd->Slot);

	// 마우스가 이동된 만큼 위젯을 이동시킵니다.
	DragStartPosition = DragStartPosition + (mousePosition - DragInputPosition);
	targetSlot->SetPosition(DragStartPosition);

	// 다음 연산을 위하여 현재 마우스 위치를 갱신시킵니다.
	DragInputPosition = mousePosition;
}

void UDraggableWndTitle::OnWidgetDragStarted()
{
	if (!IsValid(TargetWnd)) return;

	// 입력된 마우스 위치를 저장합니다.
	DragInputPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	// 드래깅 시작 위젯 위치를 저장합니다.
	DragStartPosition = Cast<UCanvasPanelSlot>(TargetWnd->Slot)->GetPosition();

	bIsDragging = true;
}

void UDraggableWndTitle::OnWidgetDragFinished()
{
	if (!IsValid(TargetWnd)) return;

	bIsDragging = false;
}

void UDraggableWndTitle::SetTitleText(FText newTitleText)
{
	Text_Title->SetText(TitleText = newTitleText);
}
