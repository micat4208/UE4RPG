#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"
#include "Enum/SlotType.h"
#include "BaseSlot.generated.h"


DECLARE_EVENT(UBaseSlot, FSlotMouseEvent)

UCLASS(Abstract)
class UE4RPG_API UBaseSlot : 
	public UUserWidget
{
	GENERATED_BODY()
	
public :
	// 마우스 오른쪽 버튼 클릭 시 발생하는 이벤트입니다.
	FSlotMouseEvent OnMouseRightButtonClickedEvent;

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

	// 마우스 클릭 입력이 있을 경우 호출됩니다.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	/// - FReply : 위젯의 이벤트가 어떠한 방법으로 처리되었는지 알리기 위한 형식

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
