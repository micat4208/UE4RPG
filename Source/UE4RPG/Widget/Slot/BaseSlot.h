#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"

#include "Enum/SlotType.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/Slot/SlotDragDropOperation/SlotDragDropOperation.h"

#include "BaseSlot.generated.h"


DECLARE_EVENT(UBaseSlot, FSlotMouseEvent)
DECLARE_EVENT_OneParam(UBaseSlot, FSlotDragEvent, USlotDragDropOperation*)

UCLASS(Abstract)
class UE4RPG_API UBaseSlot : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	TSubclassOf<class UUserWidget> BP_SlotDragWidget;

public :
	// 마우스 오른쪽 버튼 클릭 시 발생하는 이벤트입니다.
	FSlotMouseEvent OnMouseRightButtonClickedEvent;
	
	// 슬롯 드래그 시작 시 발생하는 이벤트입니다.
	FSlotDragEvent OnSlotDragStarted;

	// 슬롯 드래그 드랍 시 발생하는 이벤트입니다.
	FSlotDragEvent OnSlotDragFinished;
	
	// 드래그 취소 시 발생하는 이벤트입니다.
	FSlotDragEvent OnSlotDragCancelled;


protected :
	// 슬롯의 타입을 나타냅니다.
	ESlotType SlotType;

	// 아이템 슬롯과 함께 사용되는 코드를 나타냅니다.
	/// - 아이템 코드, 스킬 코드
	FName InCode;

	// 드래깅 작업을 허용하는지를 나타냅니다.
	bool bAllowDragOperation;

private :
	UPROPERTY(meta = (BindWidget))
	class UImage * Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage * Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Count;

public :
	UBaseSlot(const FObjectInitializer& objIniter);

protected :
	virtual void NativeConstruct() override;

	// 마우스 클릭 입력이 있을 경우 호출됩니다.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	/// - FReply : 위젯의 이벤트가 어떠한 방법으로 처리되었는지 알리기 위한 형식

	// 마우스 클릭 입력이 끝날 경우 호출됩니다.
	virtual FReply NativeOnMouseButtonUp(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;

	// 이 위젯과 마우스 겹침이 시작될 경우 호출됩니다.
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// 이 위젯과 마우스 겹침이 끝날 경우 호출됩니다.
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// 이 위젯에서 드래그가 감지될 경우 호출되는 메서드
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, 
		const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	/// - OutOperation : 출력용 매개 변수이며, 감지된 드래그 작업 객체를 반환합니다.

	// 드래그가 끝났을 경우 호출됩니다.
	virtual bool NativeOnDrop(const FGeometry& InGeometry, 
		const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// 드래그 취소 시 호출됩니다.
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, 
		UDragDropOperation* InOperation) override;

public :
	// 슬롯을 초기화합니다.
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

	// 슬롯에 표시되는 숫자를 설정합니다.
	/// - itemCount : 표시시킬 아이템 개수를 전달합니다.
	/// - bVisibleBelowOne : 1 이하일 경우 숫자 표시 여부를 전달합니다.
	void SetSlotItemCount(int32 itemCount, bool bVisibleBelowOne = false);

protected :
	TTuple<UUserWidget*, class UImage *> CreateSlotDragWidget();
	/// - 튜플
	/// - 형식의 이름을 가지지 않고, 여러 필드를 담을 수 있는 구조체입니다.
	/// - TTuple<Types...> 형식으로 선언할 수 있으며, MakeTuple 을 통해 하나의 객체를 생성할 수 있습니다.
	/// - 생성된 튜플의 필드에는 Get<index>() 로 접근할 수 있습니다.

private :
	// 슬롯 배경을 기본 색상으로 표시합니다.
	void ShowSlotNormalColor();

	// 슬롯 배경을 마우스 겹침 색상으로 표시합니다.
	void ShowSlotHoveredColor();
	
	// 슬롯 배경을 마우스 눌림 색상으로 표시합니다.
	void ShowSlotPressedColor();

public :
	FORCEINLINE class UImage* GetSlotImage() const
	{ return Image_Slot; }

	FORCEINLINE class UTextBlock* GetCountText() const
	{ return Text_Count; }

	FORCEINLINE ESlotType GetSlotType() const
	{ return SlotType; }

};
