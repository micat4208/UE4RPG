#include "ShopItemWidget.h"

#include "Widget/ClosableWnd/NpcShopWnd/NpcShopWnd.h"
#include "Widget/Slot/ItemSlot/ItemSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

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
}
