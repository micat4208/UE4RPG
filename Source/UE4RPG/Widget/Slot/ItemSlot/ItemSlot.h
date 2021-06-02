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
	class UTexture2D* T_Null;

private :
	FItemInfo ItemInfo;


public :
	UItemSlot(const FObjectInitializer& objInitializer);

public :
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode) override;

protected :
	// 아이템 이미지를 갱신합니다.
	void UpdateItemImage();

public :
	void SetItemInfo(FName itemCode);
	FORCEINLINE FItemInfo* GetItemInfo()
	{ return &ItemInfo; }
	
};
