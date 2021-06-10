#pragma once

#include "UE4RPG.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "InventoryWnd.generated.h"

UCLASS()
class UE4RPG_API UInventoryWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	TSubclassOf<class UInventoryItemSlot> BP_InventoryItemSlot;

private :
	// 생성된 인벤토리 아이템 슬롯들을 저장할 배열
	TArray<class UInventoryItemSlot*> ItemSlots;

private :
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel_ItemSlots;

public :
	UInventoryWnd(const FObjectInitializer& objectInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeInventoryWnd();

private :
	// 아이템 슬롯을 생성합니다.
	class UInventoryItemSlot * CreateItemSlot();

public :
	FORCEINLINE TArray<class UInventoryItemSlot*>& GetItemSlots()
	{ return ItemSlots; }
	
	
};
