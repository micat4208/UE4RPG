#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "Enum/Seller.h"
#include "Struct/ShopItemInfo/ShopItemInfo.h"
#include "TradeWnd.generated.h"

UCLASS()
class UE4RPG_API UTradeWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	// 연결된 슬롯 객체를 나타냅니다.
	class UItemSlot * ConnectedItemSlot;

	// 판매 아이템 정보를 나타냅니다.
	FShopItemInfo* ShopItemInfo;

	// 판매자를 나타냅니다.
	ESeller::Type Seller;

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_TradeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ItemCost;

	UPROPERTY(meta = (BindWidget))
	class UButton Button_Cancel;

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeTradeWnd(
		ESeller::Type seller,
		class UItemSlot* connectedItemSlot,
		FShopItemInfo* shopItemInfo);
	
};
