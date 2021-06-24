#include "WidgetController.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"



UWidgetController::UWidgetController(const FObjectInitializer& objIniter) :
	Super(objIniter)
{
	static ConstructorHelpers::FClassFinder<UMessageBoxWnd> BP_MESSAGE_BOX_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/MessageBoxWnd/BP_MessageBoxWnd.BP_MessageBoxWnd_C'"));
	if (BP_MESSAGE_BOX_WND.Succeeded()) BP_MessageBoxWnd = BP_MESSAGE_BOX_WND.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> BP_MESSAGE_BOX_BACKGROUND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/MessageBoxWnd/BP_MessageBoxBackground.BP_MessageBoxBackground_C'"));
	if (BP_MESSAGE_BOX_BACKGROUND.Succeeded()) BP_MessageBoxBackground = BP_MESSAGE_BOX_BACKGROUND.Class;
}

void UWidgetController::ResetInputMode(bool bForceChange)
{
	// ��� �������� ���� ������ ��Ÿ���ϴ�.
	bool bAllWidgetClosed = true;

	// �Ҵ�� Widget ���� ���� Ȯ�� ������ �߰��Ǿ� �ִ��� Ȯ���մϴ�.
	for (auto widget : AllocatedWidgets)
	{
		// ���� ���� Ȯ���� ���� ���� ������ �߰��Ǿ� �ִٸ�, ��� ������ ���� ������ ���� ���·� �����մϴ�.
		if (!IgnoreWidgets.Contains(widget))
		{
			bAllWidgetClosed = false;
			break;
		}
	}

	// AllocatedWidget ���� ���� Ȯ���� ���� ���� ������ ã�� ���ߴٸ� �Ҵ�� â������ ã���ϴ�.
	if (bAllWidgetClosed)
	{
		for (auto wnd : AllocatedWnds)
		{
			if (!IgnoreWidgets.Contains(wnd))
			{
				bAllWidgetClosed = false;
				break;
			}
		}
	}
	

	// bForceChange �� true �̰ų�, ���� ������ ������ �������� �ʴ´ٸ� �Է� ��� �ʱ�ȭ
	if (bForceChange || bAllWidgetClosed)
	{
		// �Է� ��带 �ʱ�ȭ
		PlayerController->ChangeInputModeToDefault();

		// Ŀ�� ǥ�� ����
		PlayerController->bShowMouseCursor = PlayerController->GetDefaultCursotVisibility();
	}
}

void UWidgetController::SaveWndPosition(const UClosableWnd* closableWnd)
{
	FString wndClsName = closableWnd->GetClass()->GetName();
	FVector2D wndPosition = closableWnd->GetCanvasPanelSlot()->GetPosition();

	if (PrevClosedWndPositions.Contains(wndClsName))
		PrevClosedWndPositions[wndClsName] = wndPosition;
	else PrevClosedWndPositions.Add(wndClsName, wndPosition);
}

void UWidgetController::InitializeWidgetController(ABasePlayerController* playerController)
{
	PlayerController = playerController;
}

UMessageBoxWnd* UWidgetController::CreateMessageBox(FText titleText, FText msg, bool bUseBackground, uint8 button)
{
	class UUserWidget* msgBoxBackground = nullptr;

	if (bUseBackground)
	{
		msgBoxBackground = CreateWidget<UUserWidget>(this, BP_MessageBoxBackground);
		CanvasPanel_WndParent->AddChild(msgBoxBackground);

		UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(msgBoxBackground->Slot);
		canvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		canvasPanelSlot->SetOffsets(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
	}

	// �޽��� �ڽ� ����
	UMessageBoxWnd * msgBox = Cast<UMessageBoxWnd>(CreateWnd(BP_MessageBoxWnd));
	msgBox->MsgBoxBackground = msgBoxBackground;
	msgBox->InitializeMessageBox(titleText, msg, button);

	return msgBox;
}

void UWidgetController::AddChildWidget(
	UUserWidget* childWidgetInstance, 
	bool bIgnoreThisWidget,
	EInputModeType changeInputMode,
	bool bShowMouseCursor,
	float width, float height)
{
	AllocatedWidgets.Add(childWidgetInstance);

	if (bIgnoreThisWidget) IgnoreWidgets.Add(childWidgetInstance);

	// ������ ���� ��ü�� ȭ�鿡 ���ϴ�.
	CanvasPanel_WidgetParent->AddChild(childWidgetInstance);

	// ȭ�鿡 ��� ������ ũ�⸦ �����մϴ�.
	Cast<UCanvasPanelSlot>(childWidgetInstance->Slot)->SetSize(FVector2D(width, height));
	/// - widgetInstance->Slot : widgetInstance �� Slot ��ü�� ����ϴ�.
	/// - ���� : ������ �׻� ȭ�鿡 ����� �� ���� �մϴ�.
	
	// �Է� ��带 �����մϴ�.
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);

	// Ŀ���� ���ü��� �����մϴ�.
	PlayerController->bShowMouseCursor = bShowMouseCursor;
}

void UWidgetController::CloseChildWidget(UUserWidget* childWidgetInstance)
{
	AllocatedWidgets.Remove(childWidgetInstance);

	// ������ ȭ�鿡�� �����մϴ�.
	CanvasPanel_WidgetParent->RemoveChild(childWidgetInstance);
	//childWidgetInstance->RemoveFromParent();

	// ���� Ȯ�ο��� ���ܽ�ų ������ �����ٸ� IgnoreWidgets ���� ��Ҹ� �����մϴ�.
	if (IgnoreWidgets.Contains(childWidgetInstance))
		IgnoreWidgets.Remove(childWidgetInstance);

	// �Է� ��� �ʱ�ȭ
	ResetInputMode();
}

UClosableWnd* UWidgetController::CreateWnd(
	TSubclassOf<UClosableWnd> wndClass,
	bool bUsePrevPosition,
	bool bIgnoreThisWidget,
	EInputModeType changeInputMode,
	bool bShowMouseCursor,
	float alignmentX, float alignmentY,
	float anchorMinX, float anchorMinY,
	float anchorMaxX, float anchorMaxY)
{

	// ���ο� â ������ �����մϴ�.
	UClosableWnd* newClosableWnd = CreateWidget<UClosableWnd>(this, wndClass);
	newClosableWnd->WidgetController = this;

	AllocatedWnds.Add(newClosableWnd);

	if (bIgnoreThisWidget) IgnoreWidgets.Add(newClosableWnd);

	// CanvasPanel_WndParent �� �ڽ� �������� �߰��մϴ�.
	CanvasPanel_WndParent->AddChild(newClosableWnd);

	// ������ â�� ������ ����ϴ�.
	UCanvasPanelSlot* wndSlot = newClosableWnd->GetCanvasPanelSlot();

	// Ancor, Alignment ����
	wndSlot->SetAnchors(FAnchors(anchorMinX, anchorMinY, anchorMaxX, anchorMaxY));
	wndSlot->SetAlignment(FVector2D(alignmentX, alignmentY));

	// â ũ�� ����
	wndSlot->SetSize(newClosableWnd->WndSize);

	// ���� â ��ġ�� ����Ѵٸ�
	if (bUsePrevPosition)
	{
		// ���� â ��ġ�� ��ϵǾ� �ִ��� Ȯ���մϴ�.
		FString wndClsName = newClosableWnd->GetClass()->GetName();
		if (PrevClosedWndPositions.Contains(wndClsName))
		{
			// â ��ġ�� ���� ��ġ�� �����մϴ�.
			wndSlot->SetPosition(PrevClosedWndPositions[wndClsName]);
		}
	}

	// �Է� ���, Ŀ�� ǥ��
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMouseCursor;

	return newClosableWnd;
}

void UWidgetController::CloseWnd(bool bAllClose, UClosableWnd* closableWnd)
{
	// ���� ���� â�� �������� �ʴ´ٸ� ���� X
	if (AllocatedWnds.Num() == 0) return;

	// ��� â�� �ݵ��� �Ͽ��ٸ�
	if (bAllClose)
	{
		for (auto wnd : AllocatedWnds)
		{
			// ���� ó������ ���� â�̶��
			if (!wnd->bBeClose)
			{
				// ���� Ȯ�ο��� ���ܽ�ų â�� �����ٸ� IgnoreWidgets ���� ��Ҹ� �����մϴ�.
				if (IgnoreWidgets.Contains(wnd))
					IgnoreWidgets.Remove(wnd);

				// â ���� �̺�Ʈ
				if (wnd->OnWndClosed.IsBound())
					wnd->OnWndClosed.Broadcast();

				// â�� ��ġ�� �����մϴ�.
				SaveWndPosition(wnd);

				// �θ� �������� ������ϴ�.
				CanvasPanel_WndParent->RemoveChild(wnd);

				// ���� ó��
				wnd->bBeClose = true;
			}
		}

		// �迭�� ���ϴ�.
		AllocatedWnds.Empty();
	}
	// Ư���� â�� �ݵ��� �Ͽ��ٸ�
	else
	{
		// ���� â�� �������� �ʾҴٸ� ���������� ���� â�� �ݽ��ϴ�.
		closableWnd = (closableWnd == nullptr) ? 
			AllocatedWnds[AllocatedWnds.Num() - 1] : 
			closableWnd;

		// ���� ó������ ���� â�̶��
		if (!closableWnd->bBeClose)
		{
			// ���� Ȯ�ο��� ���ܽ�ų â�� �����ٸ� IgnoreWidgets ���� ��Ҹ� �����մϴ�.
			if (IgnoreWidgets.Contains(closableWnd))
				IgnoreWidgets.Remove(closableWnd);

			// â ���� �̺�Ʈ
			if (closableWnd->OnWndClosed.IsBound())
				closableWnd->OnWndClosed.Broadcast();

			// â�� ��ġ�� �����մϴ�.
			SaveWndPosition(closableWnd);

			// �θ� �������� ������ϴ�.
			CanvasPanel_WndParent->RemoveChild(closableWnd);

			// ���� ó��
			closableWnd->bBeClose = true;

			AllocatedWnds.Remove(closableWnd);
		}
	}

	// �Է� ��� �ʱ�ȭ
	ResetInputMode();

}

void UWidgetController::SortGridPanelElem(
	UUserWidget* gridPanelElem, 
	int32 maxColumnCount, 
	int32& ref_currentColumnCount)
{
	UGridSlot* gridSlot = Cast<UGridSlot>(gridPanelElem->Slot);

	if (!IsValid(gridSlot))
	{
		UE_LOG(LogTemp, Error, 
			TEXT("%s :: %d LINE :: gridPanelElem isn't located inside the Grid Panel!"), 
			__CLSNAME__, __LINE__);
		
		return;
	}

	// �׸��� ��� ���� �����մϴ�.
	gridSlot->SetColumn(ref_currentColumnCount % maxColumnCount);
	gridSlot->SetRow(ref_currentColumnCount / maxColumnCount);
	++ref_currentColumnCount;
}
