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

	tradeWnd->OnTradeButtonClicked.AddLambda(
		[this, tradeWnd, inventoryWnd]()
		{
			// 입력 값이 잘못 되었는지 확인합니다.
			if (tradeWnd->IsInputTextEmpty() || tradeWnd->GetInputTradeCount() == 0)
			{
				WidgetController->CreateMessageBox(
					TEXT("입력 확인"),
					TEXT("입력된 내용이 잘못 되었습니다."),
					true);

				return;
			}


			// 아이템 이름
			FString itemName = tradeWnd->GetConnectedItemSlot()->GetItemInfo()->ItemName.ToString();
			FString tradeItemCount = FString::FromInt(tradeWnd->GetInputTradeCount());

			UMessageBoxWnd * msgBox = WidgetController->CreateMessageBox(
				TEXT("아이템 판매 확인"),
				itemName + TEXT("을(를) ") + tradeItemCount + TEXT("개 판매합니다."),
				true,
				EMessageBoxButton::MB_Ok | EMessageBoxButton::MB_Cancel);

			msgBox->MsgBoxButtonEvents[EMessageBoxButton::MB_Ok].AddLambda(
				[this, tradeWnd, inventoryWnd]()
				{
					UInventoryItemSlot* inventorySlot = Cast<UInventoryItemSlot>(tradeWnd->GetConnectedItemSlot());
					int32 inputCount = tradeWnd->GetInputTradeCount();

					// 아이템 제거
					GetManager(UPlayerManager)->GetPlayerInventory()->RemoveItem(
						inventorySlot->GetItemSlotIndex(), inputCount);

					// 은화 처리
					GetManager(UPlayerManager)->GetPlayerInfo()->Silver +=
						tradeWnd->GetConnectedItemSlot()->GetItemInfo()->Price * inputCount;
					inventoryWnd->UpdateSilver();


					tradeWnd->CloseThisWnd();
				});
		});


}

void UNpcShopWnd::InitializeNpcShop(FShopInfo* shopInfo)
{
	// 창 제목 설정
	SetTitleText(shopInfo->ShopName);

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

UTradeWnd* UNpcShopWnd::CreateTradeWnd(
	ESeller::Type seller,
	UItemSlot* connectedItemSlot,
	FShopItemInfo* shopItemInfo)
{
	// 이미 교환 창이 띄워져 있는 경우 추가로 띄우지 않도록 합니다.
	if (IsValid(TradeWnd)) return nullptr;

	// 아이템 정보가 비어있는 슬롯을 우클릭했다면 교환 창이 띄워지지 않도록 합니다.
	if (connectedItemSlot->GetItemInfo()->IsEmpty()) return nullptr;


	TradeWnd = Cast<UTradeWnd>(WidgetController->CreateWnd(
		BP_TradeWnd, true, false, EInputModeType::IM_Default, true));

	TradeWnd->InitializeTradeWnd(seller, connectedItemSlot, shopItemInfo);

	TradeWnd->OnWndClosed.AddLambda([this]() { TradeWnd = nullptr; });
	
	return TradeWnd;
}

void UNpcShopWnd::FloatingInventoryWnd()
{
	auto widgetController = GetManager(UPlayerManager)->GetPlayerController()->GetWidgetController();

	auto inventoryWnd = GetManager(UPlayerManager)->GetPlayerInventory()->CreateInventoryWnd(
		widgetController, EInputModeType::IM_Default, true);

	inventoryWnd->bIsTradeMode = true;

	// npc 상점 창 절반 크기를 얻습니다.
	FVector2D npcShopWndHalfSize = WndSize * 0.5f;

	// npc 상점 창 위치를 저장합니다.
	FVector2D npcShopWndPosition = GetCanvasPanelSlot()->GetPosition();

	// 인벤토리 창 절반 크기를 얻습니다.
	FVector2D inventoryWndHalfSize = inventoryWnd->WndSize * 0.5f;

	// 인벤토리 창의 위치를 계산합니다.
	FVector2D newInventoryWndPosition = npcShopWndPosition +
		((npcShopWndHalfSize + inventoryWndHalfSize) * FVector2D(1.0f, 0.0f));

	newInventoryWndPosition.Y += inventoryWndHalfSize.Y - npcShopWndHalfSize.Y;

	// 인벤토리 창의 위치를 설정합니다.
	inventoryWnd->GetCanvasPanelSlot()->SetPosition(newInventoryWndPosition);

	// 상점 창이 닫힐 때 인벤토리 창도 닫히도록 합니다.
	OnWndClosed.AddLambda([this]()
		{ GetManager(UPlayerManager)->GetPlayerInventory()->CloseInventoryWnd(); });

	// 인벤토리 슬롯 우클릭 시 아이템 판매가 이루어질 수 있도록 합니다.
	for (auto slot : inventoryWnd->GetItemSlots())
	{
		slot->OnMouseRightButtonClickedEvent.AddLambda(
			[this, inventoryWnd, slot]() { SaleItem(inventoryWnd, slot); });
	}

}
