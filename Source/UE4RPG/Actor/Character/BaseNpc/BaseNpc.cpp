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

	// �� Npc �� ��ȣ�ۿ� �� ����� ������ �����մϴ�.
	InteractableArea->OnInteractStarted.AddLambda(
		[this](UInteractableAreaComponent* interactableAreaComponent)
		{
			// PlayerController ��ü�� ����ϴ�.
			auto playerController = GetManager(UPlayerManager)->GetPlayerController();

			// NpcDialogWidget ��ü�� �����մϴ�.
			auto npcDialogWidget = CreateWidget<UNpcDialogWidget>(playerController, BP_NpcDialog);

			// ������ NpcDialogWidet �� ȭ�鿡 ���ϴ�.
			playerController->GetWidgetController()->AddChildWidget(npcDialogWidget);
		});
}
