#include "WidgetController.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"



void UWidgetController::ResetInputMode(bool bForceChange)
{
	// bForceChange 가 true 이거나, 열린 위젯의 개수가 존재하지 않는다면 입력 모드 초기화
	if (bForceChange || (AllocatedWidgets.Num() == 0))
	{
		// 입력 모드를 초기화
		PlayerController->ChangeInputModeToDefault();

		// 커서 표시 설정
		PlayerController->bShowMouseCursor = PlayerController->GetDefaultCursotVisibility();
	}
}

void UWidgetController::InitializeWidgetController(ABasePlayerController* playerController)
{
	PlayerController = playerController;
}

void UWidgetController::AddChildWidget(
	UUserWidget* childWidgetInstance, 
	EInputModeType changeInputMode,
	bool bShowMouseCursor,
	float width, float height)
{
	AllocatedWidgets.Add(childWidgetInstance);

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

	// 입력 모드 초기화
	ResetInputMode();
}
