#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "Enum/PartsType.h"
#include "PlayerEquipmentWnd.generated.h"

UCLASS()
class UE4RPG_API UPlayerEquipmentWnd final : 
	public UClosableWnd
{
	GENERATED_BODY()

private :
	// 장비 슬롯들을 나타냅니다.
	TMap<EPartsType, class UPlayerEquipSlot*> EquipSlots;
	
protected :
	virtual void NativeConstruct() override;

public :
	// 파츠 슬롯들을 갱신합니다.
	void UpdatePartsSlots();


};
