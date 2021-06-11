#include "NpcShopWnd.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/NpcShopWnd/ShopItemWidget/ShopItemWidget.h"
#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"
#include "Widget/ClosableWnd/NpcShopWnd/TradeWnd/TradeWnd.h"
#include "Widget/Slot/ItemSlot/InventoryItemSlot/InventoryItemSlot.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanelSlot.h"

UNpcShopWnd::UNpcShopWnd(const FObjectInitializer& objInitializer) :
	Super(objInitializer)
{
	static ConstructorHelpers::FClassFinder<UShopItemWidget> BP_SHOP_ITEM(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/NpcShopWnd/BP_ShopItem.BP_ShopItem_C'"));
	if (BP_SHOP_ITEM.Succeeded()) BP_ShopItem = BP_SHOP_ITEM.Class;

	static ConstructorHelpers::FClassFinder<UTradeWnd> BP_TRADE_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/NpcShopWnd/BP_TradeWnd.BP_TradeWnd_C'"));
	if (BP_TRADE_WND.Succeeded()) BP_TradeWnd = BP_TRADE_WND.Class;

	TradeWnd = nullptr;
}

void UNpcShopWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(665.0f, 600.0f);

	Button_OpenInventory->OnClicked.AddDynamic(this, &UNpcShopWnd::FloatingInventoryWnd);
}

UShopItemWidget* UNpcShopWnd::AddShopItemWidget(const FShopItemInfo& shopItemInfo)
{
	UShopItemWidget * shopItemWidget = CreateWidget<UShopItemWidget>(this, BP_ShopItem);
	GridPanel_ShopItems->AddChild(shopItemWidget);

	shopItemWidget->InitializeShopItemWidget(this, shopItemInfo);

	return shopItemWidget;
}

void UNpcShopWnd::SaleItem(UInventoryWnd* inventoryWnd, UItemSlot* itemSlot)
{
	UTradeWnd* tradeWnd = CreateTradeWnd(ESeller::Player, itemSlot);
	if (!tradeWnd) return; 


}

void UNpcShopWnd::InitializeNpcShop(FShopInfo* shopInfo)
{
	// â ���� ����
	SetTitleText(shopInfo->ShopName);

	const int maxColumnCount = 2;
	int currentColumnCount = 0;

	// �Ǹ� ������ �߰�
	for (auto shopItemInfo : shopInfo->ShopItems)
	{
		UWidgetController::SortGridPanelElem(
			AddShopItemWidget(shopItemInfo),
			maxColumnCount,
			currentColumnCount);
	}

}

UTradeWnd* UNpcShopWnd::CreateTradeWnd(
	ESeller::Type seller,
	UItemSlot* connectedItemSlot,
	FShopItemInfo* shopItemInfo)
{
	// �̹� ��ȯ â�� ����� �ִ� ��� �߰��� ����� �ʵ��� �մϴ�.
	if (IsValid(TradeWnd)) return nullptr;

	// ������ ������ ����ִ� ������ ��Ŭ���ߴٸ� ��ȯ â�� ������� �ʵ��� �մϴ�.
	if (connectedItemSlot->GetItemInfo()->IsEmpty()) return nullptr;


	TradeWnd = Cast<UTradeWnd>(WidgetController->CreateWnd(
		BP_TradeWnd, true, EInputModeType::IM_Default, true));

	TradeWnd->InitializeTradeWnd(seller, connectedItemSlot, shopItemInfo);

	TradeWnd->OnWndClosed.AddLambda([this]() { TradeWnd = nullptr; });
	
	return TradeWnd;
}

void UNpcShopWnd::FloatingInventoryWnd()
{
	auto widgetController = GetManager(UPlayerManager)->GetPlayerController()->GetWidgetController();

	auto inventoryWnd = GetManager(UPlayerManager)->GetPlayerInventory()->CreateInventoryWnd(
		widgetController, EInputModeType::IM_Default, true);

	// npc ���� â ���� ũ�⸦ ����ϴ�.
	FVector2D npcShopWndHalfSize = WndSize * 0.5f;

	// npc ���� â ��ġ�� �����մϴ�.
	FVector2D npcShopWndPosition = GetCanvasPanelSlot()->GetPosition();

	// �κ��丮 â ���� ũ�⸦ ����ϴ�.
	FVector2D inventoryWndHalfSize = inventoryWnd->WndSize * 0.5f;

	// �κ��丮 â�� ��ġ�� ����մϴ�.
	FVector2D newInventoryWndPosition = npcShopWndPosition +
		((npcShopWndHalfSize + inventoryWndHalfSize) * FVector2D(1.0f, 0.0f));

	newInventoryWndPosition.Y += inventoryWndHalfSize.Y - npcShopWndHalfSize.Y;

	// �κ��丮 â�� ��ġ�� �����մϴ�.
	inventoryWnd->GetCanvasPanelSlot()->SetPosition(newInventoryWndPosition);

	// ���� â�� ���� �� �κ��丮 â�� �������� �մϴ�.
	OnWndClosed.AddLambda([this]()
		{ GetManager(UPlayerManager)->GetPlayerInventory()->CloseInventoryWnd(); });

	// �κ��丮 ���� ��Ŭ�� �� ������ �ǸŰ� �̷���� �� �ֵ��� �մϴ�.
	for (auto slot : inventoryWnd->GetItemSlots())
	{
		slot->OnMouseRightButtonClickedEvent.AddLambda(
			[this, inventoryWnd, slot]() { SaleItem(inventoryWnd, slot); });
	}

}
