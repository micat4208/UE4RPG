#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Struct/ShopItemInfo/ShopItemInfo.h"
#include "ShopItemWidget.generated.h"



UCLASS()
class UE4RPG_API UShopItemWidget final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	class UDataTable* DT_ItemInfo;

private :
	// Npc 상점 창 객체를 나타냅니다.
	class UNpcShopWnd* NpcShopWnd;

	// 상점 아이템 정보를 나타냅니다.
	FShopItemInfo ShopItemInfo;

private : 
	UPROPERTY(meta = (BindWidget))
	class UItemSlot* ItemSlot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_ItemName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Price;

public :
	UShopItemWidget(const FObjectInitializer& ObjIniter);

public :
	void InitializeShopItemWidget(class UNpcShopWnd* npcShopWnd, FShopItemInfo shopItemInfo);
	
protected :
	// 마우스 클릭 입력이 있을 경우 호출됩니다.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;

private :
	// 아이템을 구매합니다.
	void BuyItem();

};
