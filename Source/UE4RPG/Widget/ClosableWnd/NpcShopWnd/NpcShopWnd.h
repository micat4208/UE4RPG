#pragma once

#include "UE4RPG.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Struct/ShopInfo/ShopInfo.h"
#include "Struct/ShopItemInfo/ShopItemInfo.h"

#include "Enum/Seller.h"


#include "NpcShopWnd.generated.h"

UCLASS()
class UE4RPG_API UNpcShopWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	TSubclassOf<class UShopItemWidget> BP_ShopItem;
	TSubclassOf<class UTradeWnd> BP_TradeWnd;

private :
	// ��ȯ â ��ü�� ��Ÿ���ϴ�.
	class UTradeWnd* TradeWnd;

private :
	UPROPERTY(meta = (BindWidget))
	class UGridPanel * GridPanel_ShopItems;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_OpenInventory;
	
public :
	UNpcShopWnd(const FObjectInitializer& objInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	// �Ǹ� �������� �߰��մϴ�.
	/// - shopItemInfo : �Ǹ� ������ ������ �����մϴ�.
	class UShopItemWidget* AddShopItemWidget(const FShopItemInfo& shopItemInfo);

private :
	// �������� �Ǹ��մϴ�.
	void SaleItem(class UInventoryWnd* inventoryWnd, class UItemSlot* itemSlot);

public : 
	// ���� â�� �ʱ�ȭ�մϴ�.
	void InitializeNpcShop(FShopInfo* shopInfo);

	// ������ ��ȯ â�� �����մϴ�.
	class UTradeWnd* CreateTradeWnd(ESeller::Type seller, class UItemSlot* connectedItemSlot, FShopItemInfo * shopItemInfo = nullptr);

	UFUNCTION()
	void FloatingInventoryWnd();

};
