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

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_NPC_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_NpcInfo.DT_NpcInfo'"));
	if (DT_NPC_INFO.Succeeded()) DT_NpcInfo = DT_NPC_INFO.Object;

	InteractableArea = CreateDefaultSubobject<UInteractableAreaComponent>(TEXT("INTERACTABLE_AREA_COMPONENT"));

	InteractableArea->SetupAttachment(GetRootComponent());
	InteractableArea->SetSphereRadius(250.0f);
}

void ABaseNpc::BeginPlay()
{
	Super::BeginPlay();

	// Npc 초기화
	InitializeNpc();

	// 이 Npc 와 상호작용 시 실행될 내용을 정의합니다.
	InteractableArea->OnInteractStarted.AddLambda(
		[this](UInteractableAreaComponent* interactableAreaComponent)
		{
			// PlayerController 객체를 얻습니다.
			auto playerController = GetManager(UPlayerManager)->GetPlayerController();

			// NpcDialogWidget 객체를 생성합니다.
			auto npcDialogWidget = CreateWidget<UNpcDialogWidget>(playerController, BP_NpcDialog);

			// 위젯과 연결된 Npc 객체 설정
			npcDialogWidget->ConnectedNpc = this;

			// 생성한 NpcDialogWidet 을 화면에 띄웁니다.
			playerController->GetWidgetController()->AddChildWidget(npcDialogWidget);

			// 위젯 초기화
			npcDialogWidget->InitializeDialog();
		});

}

void ABaseNpc::InitializeNpc()
{
	// NpcCode 를 이용하여 Npc 정보를 얻습니다.
	FString contextString;
	NpcInfo = DT_NpcInfo->FindRow<FNpcInfo>(NpcCode, contextString);

	// Npc 정보를 얻는 데 실패했다면
	if (NpcInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABaseNpc.cpp :: %d LINE :: NpcInfo is nullptr! (NpcCode : %s)"),
			__LINE__, *NpcCode.ToString());
	}
}
