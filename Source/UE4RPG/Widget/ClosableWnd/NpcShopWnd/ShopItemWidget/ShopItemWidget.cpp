#include "ShopItemWidget.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/ClosableWnd/NpcShopWnd/NpcShopWnd.h"
#include "Widget/Slot/ItemSlot/ItemSlot.h"
#include "Widget/ClosableWnd/NpcShopWnd/TradeWnd/TradeWnd.h"

#include "Struct/ItemInfo/ItemInfo.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UShopItemWidget::UShopItemWidget(const FObjectInitializer& ObjIniter) :
	Super(ObjIniter)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;
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
				UE_LOG(LogTemp, Error, 
					TEXT("UShopItemWidget.cpp :: %d LINE :: 입력 값이 잘못 되었습니다. (처리 필요)"), __LINE__);
				return;
			}

			FString contextString;
			FItemInfo* itemInfo = DT_ItemInfo->FindRow<FItemInfo>(
				ShopItemInfo.ItemCode, contextString);

			FItemSlotInfo newItemSlotInfo(ShopItemInfo.ItemCode, tradeWnd->GetInputTradeCount(),
				((itemInfo->ItemType == EItemType::Equipment) ? 1 : itemInfo->MaxSlotCount));

			GetManager(UPlayerManager)->GetPlayerInventory()->AddItem(newItemSlotInfo);

			tradeWnd->CloseThisWnd();
		});
}
