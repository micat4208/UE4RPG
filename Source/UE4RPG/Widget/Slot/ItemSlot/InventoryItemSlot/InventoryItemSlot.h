// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Slot/ItemSlot/ItemSlot.h"
#include "InventoryItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class UE4RPG_API UInventoryItemSlot : public UItemSlot
{
	GENERATED_BODY()

private :
	int32 ItemSlotIndex;

public :
	class UInventoryWnd* InventoryWnd;

public :
	UInventoryItemSlot(const FObjectInitializer & ObjIniter);

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeSlot(ESlotType slotType, FName itemCode, int32 itemSlotIndex);

	// 인벤토리 슬롯을 갱신합니다.
	void UpdateInventoryItemSlot();

	// 아이템 개수 텍스트를 갱신합니다.
	void UpdateItemCountText();

	// 장비 아이템을 장착합니다.
	void AttachToEquipItemSlot();

public :
	FORCEINLINE int32 GetItemSlotIndex() const
	{ return ItemSlotIndex; }


	
};
