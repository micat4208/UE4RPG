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
	// ��� ���Ե��� ��Ÿ���ϴ�.
	TMap<EPartsType, class UPlayerEquipSlot*> EquipSlots;
	
protected :
	virtual void NativeConstruct() override;

public :
	// ���� ���Ե��� �����մϴ�.
	void UpdatePartsSlots();


};
