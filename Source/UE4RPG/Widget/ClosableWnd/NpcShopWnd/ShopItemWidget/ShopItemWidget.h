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
	// Npc ���� â ��ü�� ��Ÿ���ϴ�.
	class UNpcShopWnd* NpcShopWnd;

	// ���� ������ ������ ��Ÿ���ϴ�.
	FShopItemInfo ShopItemInfo;

private : 
	UPROPERTY(meta = (BindWidget))
	class UItemSlot* ItemSlot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_ItemName;

public :
	void InitializeShopItemWidget(class UNpcShopWnd* npcShopWnd, FShopItemInfo shopItemInfo);
	
};
