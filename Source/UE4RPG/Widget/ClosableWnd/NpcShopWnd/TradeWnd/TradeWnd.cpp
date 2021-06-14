#include "TradeWnd.h"

#include "Widget/Slot/ItemSlot/ItemSlot.h"

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