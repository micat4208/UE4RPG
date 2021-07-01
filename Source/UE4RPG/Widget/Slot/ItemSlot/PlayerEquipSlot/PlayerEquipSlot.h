#pragma once

#include "CoreMinimal.h"

#include "Widget/Slot/ItemSlot/ItemSlot.h"

#include "Enum/PartsType.h"

#include "Struct/ItemSlotInfo/ItemSlotInfo.h"

#include "PlayerEquipSlot.generated.h"

UCLASS()
class UE4RPG_API UPlayerEquipSlot final : 
	public UItemSlot
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_PartsName;

private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPartsType PartsType;

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public :
	// �ش� ��� ������ ������ ���Ž�ŵ�ϴ�.
	void UpdateEquipSlot(FItemSlotInfo& itemSlotInfo);

	// ��� �������� ���� ������ŵ�ϴ�.
	void DetachToEquipItemSlot();

public :
	FORCEINLINE EPartsType GetPartsType() const
	{ return PartsType; }
	
};
