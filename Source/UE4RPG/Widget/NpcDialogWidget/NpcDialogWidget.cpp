#include "NpcDialogWidget.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/WidgetController/WidgetController.h"

#include "Components/Button.h"

void UNpcDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Exit->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnExitButtonClicked);
}

void UNpcDialogWidget::OnExitButtonClicked()
{
	ABasePlayerController * playerController = GetManager(UPlayerManager)->GetPlayerController();

	// ÀÌ À§Á¬À» ´Ý½À´Ï´Ù.
	playerController->GetWidgetController()->CloseChildWidget(this);
}
