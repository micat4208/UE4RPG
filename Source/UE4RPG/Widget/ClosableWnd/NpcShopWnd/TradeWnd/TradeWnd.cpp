#include "TradeWnd.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/Slot/ItemSlot/ItemSlot.h"
#include "Widget/Slot/ItemSlot/InventoryItemSlot/InventoryItemSlot.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

using namespace ESeller;

void UTradeWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(600.0f, 270.0f);
}

void UTradeWnd::InitializeTradeWnd(
	ESeller::Type seller, 
	UItemSlot* connectedItemSlot, 
	FShopItemInfo* shopItemInfo)
{
	Seller = seller;
	ConnectedItemSlot = connectedItemSlot;
	ShopItemInfo = shopItemInfo;

	// 타이틀 바 내용을 아이템 이름으로 설정합니다.
	SetTitleText(connectedItemSlot->GetItemInfo()->ItemName);

	// 버튼 텍스트 설정
	Text_TradeButton->SetText(FText::FromString(
		Seller == ShopKeeper ? TEXT("구매") : TEXT("판매")));

	// 아이템 가격 설정
	Text_ItemCost->SetText(
		(Seller == ShopKeeper) ?
		FText::FromString(FString::FromInt(ShopItemInfo->Cost)) :
		FText::FromString(FString::FromInt(connectedItemSlot->GetItemInfo()->Price)));

	Button_Trade->OnClicked.AddDynamic(this, &UTradeWnd::TradeButtonClicked);
	Button_Cancel->OnClicked.AddDynamic(this, &Super::CloseThisWnd);
	EditableTextBox_TradeCount->OnTextChanged.AddDynamic(this, &UTradeWnd::OnTradeCountTextChanged);

}

bool UTradeWnd::IsInputTextEmpty() const
{
	return EditableTextBox_TradeCount->GetText().IsEmpty();
}

int32 UTradeWnd::GetInputTradeCount() const
{
	return FCString::Atoi(*EditableTextBox_TradeCount->GetText().ToString());
}

void UTradeWnd::TradeButtonClicked()
{
	OnTradeButtonClicked.Broadcast();
}

void UTradeWnd::OnTradeCountTextChanged(const FText& text)
{

	// 입력되어있는 문자열이 숫자가 아니라면
	if (!text.IsNumeric())
	{
		EditableTextBox_TradeCount->SetText(FText());
		return;
	}

	// 입력된 문자열을 숫자로 변경하여 저장합니다.
	int32 tradeCount = FCString::Atoi(*text.ToString());
	int32 maxTradeCount = 0;

	switch (Seller)
	{
	case ESeller::ShopKeeper:
	{
		// 소지금
		int32 silver = GetManager(UPlayerManager)->GetPlayerInfo()->Silver;

		// 아이템 가격
		int32 price = ShopItemInfo->Cost;

		// 최대 구매 가능한 아이템 개수를 최대로 구매 가능한 아이템 개수로 설정합니다.
		/// - 장비 아이템이라면 최대 구매 가능 개수를 1 로 설정합니다.
		maxTradeCount = 
			(ConnectedItemSlot->GetItemInfo()->ItemType == EItemType::Equipment) ? 1 : 
			(silver / price);
	}
		break;

	case ESeller::Player:
		{
		// 판매하려는 아이템 슬롯 인덱스
		int32 slotIndex = Cast<UInventoryItemSlot>(ConnectedItemSlot)->GetItemSlotIndex();

		// slotIndex 번째 인벤토리 슬롯 내용을 얻습니다.
		FItemSlotInfo slotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[slotIndex];

		// 최대 판매 가능 개수를 슬롯의 아이템 개수로 설정합니다.
		maxTradeCount = slotInfo.ItemCount;
		}
		break;
	}

	// 최대 교환 개수를 초과했다면 입력된 숫자를 최대 교환 가능 개수로 설정합니다.
	if (tradeCount > maxTradeCount) tradeCount = maxTradeCount;

	// EditableTextBox 의 내용을 설정합니다.
	EditableTextBox_TradeCount->SetText(
		FText::FromString(FString::FromInt(tradeCount)));
}