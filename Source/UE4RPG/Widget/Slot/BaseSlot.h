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
	// 슬롯의 타입을 나타냅니다.
	ESlotType SlotType;

	// 아이템 슬롯과 함께 사용되는 코드를 나타냅니다.
	/// - 아이템 코드, 스킬 코드
	FName InCode;

private :
	UPROPERTY(meta = (BindWidget))
	class UImage * Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage * Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Count;

public :
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

public :
	FORCEINLINE class UImage* GetSlotImage() const
	{ return Image_Slot; }

	FORCEINLINE class UTextBlock* GetCountText() const
	{ return Text_Count; }
};
