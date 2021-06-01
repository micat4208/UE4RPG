#pragma once

#include "Widget/Slot/BaseSlot.h"
#include "Struct/ItemInfo/ItemInfo.h"
#include "ItemSlot.generated.h"



UCLASS()
class UE4RPG_API UItemSlot : public UBaseSlot
{
	GENERATED_BODY()

private :
	class UDataTable* DT_ItemInfo;

private :
	FItemInfo ItemInfo;

public :
	UItemSlot(const FObjectInitializer& objInitializer);

public :
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode) override;

public :
	void SetItemInfo(FName itemCode);
	FORCEINLINE FItemInfo* GetItemInfo()
	{ return &ItemInfo; }
	
};
