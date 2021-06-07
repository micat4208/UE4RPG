#pragma once

#include "UE4RPG.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Struct/ShopInfo/ShopInfo.h"
#include "Struct/ShopItemInfo/ShopItemInfo.h"

#include "NpcShopWnd.generated.h"

UCLASS()
class UE4RPG_API UNpcShopWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	TSubclassOf<class UShopItemWidget> BP_ShopItem;

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
	// 판매 아이템을 추가합니다.
	/// - shopItemInfo : 판매 아이템 정보를 전달합니다.
	class UShopItemWidget* AddShopItemWidget(const FShopItemInfo& shopItemInfo);

public : 
	// 상점 창을 초기화합니다.
	void InitializeNpcShop(FShopInfo* shopInfo);

	UFUNCTION()
	void FloatingInventoryWnd();

};
