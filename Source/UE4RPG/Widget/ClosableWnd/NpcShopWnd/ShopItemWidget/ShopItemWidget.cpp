#include "ShopItemWidget.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/NpcShopWnd/NpcShopWnd.h"
#include "Widget/Slot/ItemSlot/ItemSlot.h"
#include "Widget/ClosableWnd/NpcShopWnd/TradeWnd/TradeWnd.h"
#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"

#include "Struct/ItemInfo/ItemInfo.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UShopItemWidget::UShopItemWidget(const FObjectInitializer& ObjIniter) :
	Super(ObjIniter)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;

	WidgetController = nullptr;
}

void UShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetController = GetManager(UPlayerManager)->GetPlayerController()->GetWidgetController();
}

void UShopItemWidget::InitializeShopItemWidget(UNpcShopWnd* npcShopWnd, FShopItemInfo shopItemInfo)
{
	NpcShopWnd = npcShopWnd;
	ShopItemInfo = shopItemInfo;

	// 아이템 슬롯 초기화
	ItemSlot->InitializeSlot(ESlotType::ShopItemSlot, ShopItemInfo.ItemCode);

	// 아이템 이름 설정
	Text_ItemName->SetText(ItemSlot->GetItemInfo()->ItemName);

	// 가격 설정
	Text_Price->SetText(FText::FromString(FString::FromInt(ShopItemInfo.Cost)));

}

FReply UShopItemWidget::NativeOnMouseButtonDown(
	const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	// 마우스 우클릭이 발생했다면
	if (inMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// 아이템 구매
		BuyItem();

		// 이벤트 처리됨.
		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
}

void UShopItemWidget::BuyItem()
{
	UTradeWnd* tradeWnd = NpcShopWnd->CreateTradeWnd(ESeller::ShopKeeper, ItemSlot, &ShopItemInfo);
	if (!tradeWnd) return;

	tradeWnd->OnTradeButtonClicked.AddLambda(
		[this, tradeWnd]()
		{
			// 입력 값이 잘못되었을 경우
			if (tradeWnd->IsInputTextEmpty() || tradeWnd->GetInputTradeCount() == 0)
			{
				// 메시지 박스 띄우기
				WidgetController->CreateMessageBox(
					TEXT("입력 확인"),
					TEXT("입력된 내용이 잘못 되었습니다."), 
					true);
				return;
			}

			FString itemName = tradeWnd->GetConnectedItemSlot()->GetItemInfo()->ItemName.ToString();
			FString tradeCount = FString::FromInt(tradeWnd->GetInputTradeCount());

			UMessageBoxWnd * msgBox = WidgetController->CreateMessageBox(
				TEXT("아이템 구매 확인"),
				itemName + FString(TEXT("을(를) ")) + tradeCount + FString(TEXT("개 구매합니다.")),
				true,
				EMessageBoxButton::MB_Ok | EMessageBoxButton::MB_Cancel);

			msgBox->MsgBoxButtonEvents[EMessageBoxButton::MB_Ok].AddLambda(
				[this, tradeWnd]()
				{
					FString contextString;
					FItemInfo* itemInfo = DT_ItemInfo->FindRow<FItemInfo>(
						ShopItemInfo.ItemCode, contextString);

					FItemSlotInfo newItemSlotInfo(ShopItemInfo.ItemCode, tradeWnd->GetInputTradeCount(),
						((itemInfo->ItemType == EItemType::Equipment) ? 1 : itemInfo->MaxSlotCount));

					// 인벤토리 객체
					UPlayerInventory* playerInventory = GetManager(UPlayerManager)->GetPlayerInventory();

					// 인벤토리에 아이템 추가
					playerInventory->AddItem(newItemSlotInfo);

					// 소지금 감소
					int32 cost = tradeWnd->GetInputTradeCount() * tradeWnd->GetShopItemInfo()->Cost;
					GetManager(UPlayerManager)->GetPlayerInfo()->Silver -= cost;

					UInventoryWnd* inventoryWnd = playerInventory->GetInventoryWnd();
					if (IsValid(inventoryWnd))
						inventoryWnd->UpdateSilver();

					tradeWnd->CloseThisWnd();
				});


		});
}
