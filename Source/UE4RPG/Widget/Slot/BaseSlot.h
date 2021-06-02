#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"
#include "Enum/SlotType.h"
#include "BaseSlot.generated.h"

UCLASS(Abstract)
class UE4RPG_API UBaseSlot : 
	public UUserWidget
{
	GENERATED_BODY()
	
protected :
	// ������ Ÿ���� ��Ÿ���ϴ�.
	ESlotType SlotType;

	// ������ ���԰� �Բ� ���Ǵ� �ڵ带 ��Ÿ���ϴ�.
	/// - ������ �ڵ�, ��ų �ڵ�
	FName InCode;

private :
	UPROPERTY(meta = (BindWidget))
	class UImage * Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage * Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Count;

public :
	// ������ �ʱ�ȭ�մϴ�.
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

public :
	FORCEINLINE class UImage* GetSlotImage() const
	{ return Image_Slot; }

	FORCEINLINE class UTextBlock* GetCountText() const
	{ return Text_Count; }
};
