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

protected :
	virtual void NativeConstruct() override;

public :
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

	// 슬롯에 표시되는 숫자를 설정합니다.
	/// - itemCount : 표시시킬 아이템 개수를 전달합니다.
	/// - bVisibleBelowOne : 1 이하일 경우 숫자 표시 여부를 전달합니다.
	void SetSlotItemCount(int32 itemCount, bool bVisibleBelowOne = false);

public :
	FORCEINLINE class UImage* GetSlotImage() const
	{ return Image_Slot; }

	FORCEINLINE class UTextBlock* GetCountText() const
	{ return Text_Count; }
};
