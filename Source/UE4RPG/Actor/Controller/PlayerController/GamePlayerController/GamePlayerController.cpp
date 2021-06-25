#include "GamePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/PlayerHUD/PlayerHUD.h"

#include "Component/PlayerBehaviorBroadcast/PlayerBehaviorBroadcastComponent.h"
#include "Components/CanvasPanelSlot.h"

#include "Struct/ItemBehaviorInfo/ItemBehaviorInfo.h"
#include "Struct/ItemInfo/ItemInfo.h"

AGamePlayerController::AGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<UPlayerHUD> BP_PLAYER_HUD(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/PlayerHUD/BP_PlayerHUD.BP_PlayerHUD_C'"));
	if (BP_PLAYER_HUD.Succeeded()) BP_PlayerHUD = BP_PLAYER_HUD.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_BEHAVIOR_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemBehaviorInfo.DT_ItemBehaviorInfo'"));
	if (DT_ITEM_BEHAVIOR_INFO.Succeeded()) DT_ItemBehaviorInfo = DT_ITEM_BEHAVIOR_INFO.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;

}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("OpenInventory"), EInputEvent::IE_Pressed,
		this, &ThisClass::OpenInventory);

	// MouseX, Y 입력 시 호출할 메서드를 바인딩시킵니다.
	InputComponent->BindAxis(TEXT("MouseX"), this, &AGamePlayerController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &AGamePlayerController::MouseYInput);
}

void AGamePlayerController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	// 캐릭터 초기화
	GetManager(UPlayerManager)->InitializePlayerCharacter();

#pragma region Register Item Use Event
	// 인벤토리 아이템 사용에 대한 이벤트 처리
	(*GetPlayerBehaviorBroadcast())[EPlayerBehavior::BH_UseInventoryItem].AddLambda(
		[this](FPlayerBehaviorData& bhData)
		{
			// 플레이어 인벤토리 정보를 얻습니다.
			TArray<FItemSlotInfo>& inventoryItemInfos = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos;

			// 아이템 사용 이벤트를 발생시킨 슬롯 인덱스를 얻습니다.
			int32 inventoryItemSlotIndex = bhData.GetInventoryItemSlotIndex();

			// 아이템을 사용한 슬롯 정보를 얻습니다.
			FItemSlotInfo& itemSlotInfo = inventoryItemInfos[bhData.GetInventoryItemSlotIndex()];

			// 사용한 아이템을 인벤토리에서 제거합니다.
			GetManager(UPlayerManager)->GetPlayerInventory()->RemoveItem(
				inventoryItemSlotIndex,
				bhData.GetItemCount());

			// 사용된 아이템 코드를 얻습니다.
			FName usedItemCode = bhData.GetCode();

			// 사용된 아이템 정보를 얻습니다.
			FString contextString;
			FItemInfo * usedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(usedItemCode, contextString);

			// 아이템 사용 효과 코드를 얻습니다.
			if (usedItemInfo->ItemBehaviorCode.IsNone()) return;
			FItemBehaviorInfo* itemBHInfo = DT_ItemBehaviorInfo->FindRow<FItemBehaviorInfo>(
				usedItemInfo->ItemBehaviorCode, contextString);

			// 아이템 사용에 대한 처리를 합니다.
			for (auto itemBehavior : itemBHInfo->ItemBehaviors)
			{
				GetManager(UPlayerManager)->GetPlayerInfo()->AddStatusAttributes(
					itemBehavior.Key, itemBehavior.Value);
			}

		});

#pragma endregion

	CreatePlayerHUD();
}

void AGamePlayerController::CreatePlayerHUD()
{
	UPlayerHUD * playerHUD = CreateWidget<UPlayerHUD>(this, BP_PlayerHUD);
	GetWidgetController()->AddChildWidget(playerHUD, true, EInputModeType::IM_Default, false, 400.0f, 120.0f);

	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(playerHUD->Slot);
	canvasPanelSlot->SetPosition(FVector2D(50.0f, 50.0f));
	canvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
	canvasPanelSlot->SetAlignment(FVector2D(0.0f, 0.0f));
}

void AGamePlayerController::MouseXInput(float axis)
{
	// 컨트롤러의 Yaw 회전값에 axis 를 더합니다.
	/// - axis : 마우스를 왼쪽으로 이동시킨다면 -1
	/// -        마우스를 오른쪽으로 이동시킨다면 1
	AddYawInput(axis);
}

void AGamePlayerController::MouseYInput(float axis)
{
	// 컨트롤러의 Pitch 회전값에 axis 를 더합니다.
	/// - axis : 마우스를 위쪽으로 이동시킨다면 -1
	/// -        마우스를 아래쪽으로 이동시킨다면 1
	AddPitchInput(axis);
}

void AGamePlayerController::OpenInventory()
{
	GetManager(UPlayerManager)->GetPlayerInventory()->ToggleInventoryWnd(GetWidgetController());
}
