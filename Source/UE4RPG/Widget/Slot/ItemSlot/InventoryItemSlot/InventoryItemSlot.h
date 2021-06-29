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

	// �κ��丮 ������ �����մϴ�.
	void UpdateInventoryItemSlot();

	// ������ ���� �ؽ�Ʈ�� �����մϴ�.
	void UpdateItemCountText();

	// ��� �������� �����մϴ�.
	//void AttachToEquipItemSlot(class UPlayerEquipSlot* targetEquipSlot = nullptr);

public :
	FORCEINLINE int32 GetItemSlotIndex() const
	{ return ItemSlotIndex; }


	
};
