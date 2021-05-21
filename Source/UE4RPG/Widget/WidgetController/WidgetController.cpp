#include "WidgetController.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Components/CanvasPanel.h"



void UWidgetController::InitializeWidgetController(ABasePlayerController* playerController)
{
	PlayerController = playerController;
}

void UWidgetController::AddChildWidget(UUserWidget* childWidgetInstance)
{
	CanvasPanel_WidgetParent->AddChild(childWidgetInstance);
}
