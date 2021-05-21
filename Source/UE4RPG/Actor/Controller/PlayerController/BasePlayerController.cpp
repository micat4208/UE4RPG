#include "BasePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Widget/WidgetController/WidgetController.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UWidgetController> BP_WIDGET_CONTROLLER(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WidgetController/BP_WidgetController.BP_WidgetController_C'"));
	if (BP_WIDGET_CONTROLLER.Succeeded()) BP_WidgetController = BP_WIDGET_CONTROLLER.Class;
}

void ABasePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	GetManager(UPlayerManager)->RegisterPlayer(this, Cast<APlayerCharacter>(aPawn));

	WidgetController = CreateWidget<UWidgetController>(this, BP_WidgetController);
	WidgetController->InitializeWidgetController(this);
	WidgetController->AddToViewport();

	
}