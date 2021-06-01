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
	// ���� â�� �ʱ�ȭ�մϴ�.
	void InitializeNpcShop(FShopInfo* shopInfo);

};
