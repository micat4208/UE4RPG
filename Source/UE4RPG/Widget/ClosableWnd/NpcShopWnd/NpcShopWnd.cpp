#include "NpcShopWnd.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/NpcShopWnd/ShopItemWidget/ShopItemWidget.h"

#include "Components/GridPanel.h"

UNpcShopWnd::UNpcShopWnd(const FObjectInitializer& objInitializer) :
	Super(objInitializer)
{
	static ConstructorHelpers::FClassFinder<UShopItemWidget> BP_SHOP_ITEM(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/NpcShopWnd/BP_ShopItem.BP_ShopItem_C'"));
	if (BP_SHOP_ITEM.Succeeded()) BP_ShopItem = BP_SHOP_ITEM.Class;


}

void UNpcShopWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(665.0f, 600.0f);


}

UShopItemWidget* UNpcShopWnd::AddShopItemWidget(const FShopItemInfo& shopItemInfo)
{
	UShopItemWidget * shopItemWidget = CreateWidget<UShopItemWidget>(this, BP_ShopItem);
	GridPanel_ShopItems->AddChild(shopItemWidget);

	shopItemWidget->InitializeShopItemWidget(this, shopItemInfo);

	return shopItemWidget;
}

void UNpcShopWnd::InitializeNpcShop(FShopInfo* shopInfo)
{

	const int maxColumnCount = 2;
	int currentColumnCount = 0;

	// 판매 아이템 추가
	for (auto shopItemInfo : shopInfo->ShopItems)
	{
		UWidgetController::SortGridPanelElem(
			AddShopItemWidget(shopItemInfo),
			maxColumnCount,
			currentColumnCount);
	}

}
