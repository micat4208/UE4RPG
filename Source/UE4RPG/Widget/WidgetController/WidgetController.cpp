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
	// 모든 위젯들이 닫혀 있음을 나타냅니다.
	bool bAllWidgetClosed = true;

	// 할당된 Widget 들중 닫힘 확인 위젯이 추가되어 있는지 확인합니다.
	for (auto widget : AllocatedWidgets)
	{
		// 만약 닫힘 확인을 하지 않을 위젯이 추가되어 있다면, 모든 위젯이 아직 닫히지 않음 상태로 설정합니다.
		if (!IgnoreWidgets.Contains(widget))
		{
			bAllWidgetClosed = false;
			break;
		}
	}

	// AllocatedWidget 에서 닫힘 확인을 하지 않을 위젯을 찾지 못했다면 할당된 창에서도 찾습니다.
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
	

	// bForceChange 가 true 이거나, 열린 위젯의 개수가 존재하지 않는다면 입력 모드 초기화
	if (bForceChange || bAllWidgetClosed)
	{
		// 입력 모드를 초기화
		PlayerController->ChangeInputModeToDefault();

		// 커서 표시 설정
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

	// 메시지 박스 생성
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

	// 전달할 위젯 객체를 화면에 띄웁니다.
	CanvasPanel_WidgetParent->AddChild(childWidgetInstance);

	// 화면에 띄운 위젯의 크기를 설정합니다.
	Cast<UCanvasPanelSlot>(childWidgetInstance->Slot)->SetSize(FVector2D(width, height));
	/// - widgetInstance->Slot : widgetInstance 의 Slot 객체를 얻습니다.
	/// - 주의 : 슬롯은 항상 화면에 띄워진 후 얻어야 합니다.
	
	// 입력 모드를 설정합니다.
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);

	// 커서의 가시성을 설정합니다.
	PlayerController->bShowMouseCursor = bShowMouseCursor;
}

void UWidgetController::CloseChildWidget(UUserWidget* childWidgetInstance)
{
	AllocatedWidgets.Remove(childWidgetInstance);

	// 위젯을 화면에서 제거합니다.
	CanvasPanel_WidgetParent->RemoveChild(childWidgetInstance);
	//childWidgetInstance->RemoveFromParent();

	// 닫힘 확인에서 제외시킬 위젯이 닫힌다면 IgnoreWidgets 에서 요소를 제거합니다.
	if (IgnoreWidgets.Contains(childWidgetInstance))
		IgnoreWidgets.Remove(childWidgetInstance);

	// 입력 모드 초기화
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

	// 새로운 창 위젯을 생성합니다.
	UClosableWnd* newClosableWnd = CreateWidget<UClosableWnd>(this, wndClass);
	newClosableWnd->WidgetController = this;

	AllocatedWnds.Add(newClosableWnd);

	if (bIgnoreThisWidget) IgnoreWidgets.Add(newClosableWnd);

	// CanvasPanel_WndParent 의 자식 위젯으로 추가합니다.
	CanvasPanel_WndParent->AddChild(newClosableWnd);

	// 생성된 창의 슬롯을 얻습니다.
	UCanvasPanelSlot* wndSlot = newClosableWnd->GetCanvasPanelSlot();

	// Ancor, Alignment 설정
	wndSlot->SetAnchors(FAnchors(anchorMinX, anchorMinY, anchorMaxX, anchorMaxY));
	wndSlot->SetAlignment(FVector2D(alignmentX, alignmentY));

	// 창 크기 설정
	wndSlot->SetSize(newClosableWnd->WndSize);

	// 이전 창 위치를 사용한다면
	if (bUsePrevPosition)
	{
		// 이전 창 위치가 기록되어 있는지 확인합니다.
		FString wndClsName = newClosableWnd->GetClass()->GetName();
		if (PrevClosedWndPositions.Contains(wndClsName))
		{
			// 창 위치를 이전 위치로 설정합니다.
			wndSlot->SetPosition(PrevClosedWndPositions[wndClsName]);
		}
	}

	// 입력 모드, 커서 표시
	PlayerController->SetInputModeFromNewInputModeType(changeInputMode);
	PlayerController->bShowMouseCursor = bShowMouseCursor;

	return newClosableWnd;
}

void UWidgetController::CloseWnd(bool bAllClose, UClosableWnd* closableWnd)
{
	// 만약 열린 창이 존재하지 않는다면 실행 X
	if (AllocatedWnds.Num() == 0) return;

	// 모든 창을 닫도록 하였다면
	if (bAllClose)
	{
		for (auto wnd : AllocatedWnds)
		{
			// 닫힘 처리되지 않은 창이라면
			if (!wnd->bBeClose)
			{
				// 닫힘 확인에서 제외시킬 창이 닫힌다면 IgnoreWidgets 에서 요소를 제거합니다.
				if (IgnoreWidgets.Contains(wnd))
					IgnoreWidgets.Remove(wnd);

				// 창 닫힘 이벤트
				if (wnd->OnWndClosed.IsBound())
					wnd->OnWndClosed.Broadcast();

				// 창의 위치를 저장합니다.
				SaveWndPosition(wnd);

				// 부모 위젯에서 떼어냅니다.
				CanvasPanel_WndParent->RemoveChild(wnd);

				// 닫힘 처리
				wnd->bBeClose = true;
			}
		}

		// 배열을 비웁니다.
		AllocatedWnds.Empty();
	}
	// 특정한 창을 닫도록 하였다면
	else
	{
		// 닫을 창이 지정되지 않았다면 마지막으로 열린 창을 닫습니다.
		closableWnd = (closableWnd == nullptr) ? 
			AllocatedWnds[AllocatedWnds.Num() - 1] : 
			closableWnd;

		// 닫힘 처리되지 않은 창이라면
		if (!closableWnd->bBeClose)
		{
			// 닫힘 확인에서 제외시킬 창이 닫힌다면 IgnoreWidgets 에서 요소를 제거합니다.
			if (IgnoreWidgets.Contains(closableWnd))
				IgnoreWidgets.Remove(closableWnd);

			// 창 닫힘 이벤트
			if (closableWnd->OnWndClosed.IsBound())
				closableWnd->OnWndClosed.Broadcast();

			// 창의 위치를 저장합니다.
			SaveWndPosition(closableWnd);

			// 부모 위젯에서 떼어냅니다.
			CanvasPanel_WndParent->RemoveChild(closableWnd);

			// 닫힘 처리
			closableWnd->bBeClose = true;

			AllocatedWnds.Remove(closableWnd);
		}
	}

	// 입력 모드 초기화
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

	// 그리드 행과 열을 설정합니다.
	gridSlot->SetColumn(ref_currentColumnCount % maxColumnCount);
	gridSlot->SetRow(ref_currentColumnCount / maxColumnCount);
	++ref_currentColumnCount;
}
