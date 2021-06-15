#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "Enum/Seller.h"
#include "Struct/ShopItemInfo/ShopItemInfo.h"
#include "TradeWnd.generated.h"

DECLARE_EVENT(UTradeWnd, FTradeWndButtonEvent)

UCLASS()
class UE4RPG_API UTradeWnd : public UClosableWnd
{
	GENERATED_BODY()

public :
	FTradeWndButtonEvent OnTradeButtonClicked;

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
	class UButton* Button_Trade;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Cancel;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox * EditableTextBox_TradeCount;

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeTradeWnd(
		ESeller::Type seller,
		class UItemSlot* connectedItemSlot,
		FShopItemInfo* shopItemInfo);

	// EditableTextBox_TradeCount 에 입력된 문자열이 비어있는지 확인합니다.
	bool IsInputTextEmpty() const;

	// EditableTextBox_TradeCount 에 입력된 값을 숫자로 반환합니다.
	int32 GetInputTradeCount() const;

private :
	UFUNCTION()
	void TradeButtonClicked();

	UFUNCTION()
	void OnTradeCountTextChanged(const FText& text);

public :
	FORCEINLINE class UItemSlot* GetConnectedItemSlot() const
	{ return ConnectedItemSlot; }


	
};
