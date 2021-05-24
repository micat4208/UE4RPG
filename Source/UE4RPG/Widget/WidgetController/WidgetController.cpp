#include "WidgetController.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"



void UWidgetController::ResetInputMode(bool bForceChange)
{
	// bForceChange �� true �̰ų�, ���� ������ ������ �������� �ʴ´ٸ� �Է� ��� �ʱ�ȭ
	if (bForceChange || (AllocatedWidgets.Num() == 0))
	{
		// �Է� ��带 �ʱ�ȭ
		PlayerController->ChangeInputModeToDefault();

		// Ŀ�� ǥ�� ����
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

	// �Է� ��� �ʱ�ȭ
	ResetInputMode();
}
