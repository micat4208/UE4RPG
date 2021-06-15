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
	// ����� ���� ��ü�� ��Ÿ���ϴ�.
	class UItemSlot * ConnectedItemSlot;

	// �Ǹ� ������ ������ ��Ÿ���ϴ�.
	FShopItemInfo* ShopItemInfo;

	// �Ǹ��ڸ� ��Ÿ���ϴ�.
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

	// EditableTextBox_TradeCount �� �Էµ� ���ڿ��� ����ִ��� Ȯ���մϴ�.
	bool IsInputTextEmpty() const;

	// EditableTextBox_TradeCount �� �Էµ� ���� ���ڷ� ��ȯ�մϴ�.
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
