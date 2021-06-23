#include "GamePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/PlayerHUD/PlayerHUD.h"

#include "Component/PlayerBehaviorBroadcast/PlayerBehaviorBroadcastComponent.h"
#include "Components/CanvasPanelSlot.h"

AGamePlayerController::AGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<UPlayerHUD> BP_PLAYER_HUD(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/PlayerHUD/BP_PlayerHUD.BP_PlayerHUD_C'"));
	if (BP_PLAYER_HUD.Succeeded()) BP_PlayerHUD = BP_PLAYER_HUD.Class;
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("OpenInventory"), EInputEvent::IE_Pressed,
		this, &ThisClass::OpenInventory);

	// MouseX, Y �Է� �� ȣ���� �޼��带 ���ε���ŵ�ϴ�.
	InputComponent->BindAxis(TEXT("MouseX"), this, &AGamePlayerController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &AGamePlayerController::MouseYInput);
}

void AGamePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

#pragma region Register Item Use Event
	// �κ��丮 ������ ��뿡 ���� �̺�Ʈ ó��
	(*GetPlayerBehaviorBroadcast())[EPlayerBehavior::BH_UseInventoryItem].AddLambda(
		[this](FPlayerBehaviorData& bhData)
		{
			// �÷��̾� �κ��丮 ������ ����ϴ�.
			TArray<FItemSlotInfo>& inventoryItemInfos = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos;

			// ������ ��� �̺�Ʈ�� �߻���Ų ���� �ε����� ����ϴ�.
			int32 inventoryItemSlotIndex = bhData.GetInventoryItemSlotIndex();

			// �������� ����� ���� ������ ����ϴ�.
			FItemSlotInfo& itemSlotInfo = inventoryItemInfos[bhData.GetInventoryItemSlotIndex()];

			// ����� �������� �κ��丮���� �����մϴ�.
			GetManager(UPlayerManager)->GetPlayerInventory()->RemoveItem(
				inventoryItemSlotIndex,
				bhData.GetItemCount());
		});

#pragma endregion

	CreatePlayerHUD();
}

void AGamePlayerController::CreatePlayerHUD()
{
	UPlayerHUD * playerHUD = CreateWidget<UPlayerHUD>(this, BP_PlayerHUD);
	GetWidgetController()->AddChildWidget(playerHUD, EInputModeType::IM_Default, false, 400.0f, 120.0f);

	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(playerHUD->Slot);
	canvasPanelSlot->SetPosition(FVector2D(50.0f, 50.0f));
	canvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
	canvasPanelSlot->SetAlignment(FVector2D(0.0f, 0.0f));
}

void AGamePlayerController::MouseXInput(float axis)
{
	// ��Ʈ�ѷ��� Yaw ȸ������ axis �� ���մϴ�.
	/// - axis : ���콺�� �������� �̵���Ų�ٸ� -1
	/// -        ���콺�� ���������� �̵���Ų�ٸ� 1
	AddYawInput(axis);
}

void AGamePlayerController::MouseYInput(float axis)
{
	// ��Ʈ�ѷ��� Pitch ȸ������ axis �� ���մϴ�.
	/// - axis : ���콺�� �������� �̵���Ų�ٸ� -1
	/// -        ���콺�� �Ʒ������� �̵���Ų�ٸ� 1
	AddPitchInput(axis);
}

void AGamePlayerController::OpenInventory()
{
	GetManager(UPlayerManager)->GetPlayerInventory()->ToggleInventoryWnd(GetWidgetController());
}
