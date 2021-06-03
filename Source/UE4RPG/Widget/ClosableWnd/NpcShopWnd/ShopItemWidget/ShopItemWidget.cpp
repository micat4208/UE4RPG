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
