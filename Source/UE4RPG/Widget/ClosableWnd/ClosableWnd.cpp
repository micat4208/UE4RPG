#include "ClosableWnd.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/DraggableWndTitle/DraggableWndTitle.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	bBeClose = false;

	// 드래그 타깃을 자신으로 설정합니다.
	DraggableWndTitle->SetDragTarget(this);

	// 창 크기를 설정합니다.
	WndSize = FVector2D(500.0f, 600.0f);

	// 타이틀바의 닫기 버튼 이벤트 설정
	DraggableWndTitle->GetCloseButton()->OnClicked.AddDynamic(this, &UClosableWnd::CloseThisWnd);
}

void UClosableWnd::SetTitleText(FText newTitleText)
{
	DraggableWndTitle->SetTitleText(newTitleText);
}

void UClosableWnd::CloseThisWnd()
{
	// 닫힘 처리된 창이라면 실행 X
	if (bBeClose) return;

	WidgetController->CloseWnd(
		/*bAllClose   = */ false, 
		/*closableWnd = */ this);
}

UCanvasPanelSlot* UClosableWnd::GetCanvasPanelSlot() const
{ 
	return Cast<UCanvasPanelSlot>(Slot); 
}
