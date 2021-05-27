#include "ClosableWnd.h"

#include "Widget/ClosableWnd/DraggableWndTitle/DraggableWndTitle.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// 드래그 타깃을 자신으로 설정합니다.
	DraggableWndTitle->SetDragTarget(this);

}
