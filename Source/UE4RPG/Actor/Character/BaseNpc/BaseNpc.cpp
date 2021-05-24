#include "BaseNpc.h"

#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/RPGGameInstance.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "Widget/WidgetController/WidgetController.h"

#include "Component/InteractableArea/InteractableAreaComponent.h"

ABaseNpc::ABaseNpc()
{
	static ConstructorHelpers::FClassFinder<UNpcDialogWidget> BP_NPC_DIALOG(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/NpcDialog/BP_NpcDialog.BP_NpcDialog_C'"));
	if (BP_NPC_DIALOG.Succeeded()) BP_NpcDialog = BP_NPC_DIALOG.Class;

	InteractableArea = CreateDefaultSubobject<UInteractableAreaComponent>(TEXT("INTERACTABLE_AREA_COMPONENT"));

	InteractableArea->SetupAttachment(GetRootComponent());
	InteractableArea->SetSphereRadius(250.0f);
	
}

void ABaseNpc::BeginPlay()
{
	Super::BeginPlay();

	// 이 Npc 와 상호작용 시 실행될 내용을 정의합니다.
	InteractableArea->OnInteractStarted.AddLambda(
		[this](UInteractableAreaComponent* interactableAreaComponent)
		{
			// PlayerController 객체를 얻습니다.
			auto playerController = GetManager(UPlayerManager)->GetPlayerController();

			// NpcDialogWidget 객체를 생성합니다.
			auto npcDialogWidget = CreateWidget<UNpcDialogWidget>(playerController, BP_NpcDialog);

			// 생성한 NpcDialogWidet 을 화면에 띄웁니다.
			playerController->GetWidgetController()->AddChildWidget(npcDialogWidget);
		});
}
