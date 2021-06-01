#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Struct/ShopInfo/ShopInfo.h"

#include "NpcShopWnd.generated.h"

UCLASS()
class UE4RPG_API UNpcShopWnd : public UClosableWnd
{
	GENERATED_BODY()
	
protected :
	virtual void NativeConstruct() override;

public : 
	// 상점 창을 초기화합니다.
	void InitializeNpcShop(FShopInfo* shopInfo);

};
