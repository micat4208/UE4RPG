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
	class UButton Button_Cancel;

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeTradeWnd(
		ESeller::Type seller,
		class UItemSlot* connectedItemSlot,
		FShopItemInfo* shopItemInfo);
	
};
