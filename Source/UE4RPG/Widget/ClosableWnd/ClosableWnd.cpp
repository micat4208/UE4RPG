#include "ClosableWnd.h"

#include "Widget/ClosableWnd/DraggableWndTitle/DraggableWndTitle.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	// �巡�� Ÿ���� �ڽ����� �����մϴ�.
	DraggableWndTitle->SetDragTarget(this);

}
