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

public :
	// 해당 장비 아이템 슬롯을 갱신시킵니다.
	void UpdateEquipSlot(FItemSlotInfo& itemSlotInfo);

public :
	FORCEINLINE EPartsType GetPartsType() const
	{ return PartsType; }
	
};
