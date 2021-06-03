#include "ShopItemWidget.h"

#include "Widget/ClosableWnd/NpcShopWnd/NpcShopWnd.h"
#include "Widget/Slot/ItemSlot/ItemSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UShopItemWidget::InitializeShopItemWidget(UNpcShopWnd* npcShopWnd, FShopItemInfo shopItemInfo)
{
	NpcShopWnd = npcShopWnd;
	ShopItemInfo = shopItemInfo;

	// ������ ���� �ʱ�ȭ
	ItemSlot->InitializeSlot(ESlotType::ShopItemSlot, ShopItemInfo.ItemCode);

	// ������ �̸� ����
	Text_ItemName->SetText(ItemSlot->GetItemInfo()->ItemName);

	// ���� ����
	Text_Price->SetText(FText::FromString(FString::FromInt(ShopItemInfo.Cost)));

}
