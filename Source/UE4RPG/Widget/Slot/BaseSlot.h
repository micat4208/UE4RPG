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
	// ���콺 ������ ��ư Ŭ�� �� �߻��ϴ� �̺�Ʈ�Դϴ�.
	FSlotMouseEvent OnMouseRightButtonClickedEvent;
	
	// ���� �巡�� ���� �� �߻��ϴ� �̺�Ʈ�Դϴ�.
	FSlotDragEvent OnSlotDragStarted;

	// ���� �巡�� ��� �� �߻��ϴ� �̺�Ʈ�Դϴ�.
	FSlotDragEvent OnSlotDragFinished;
	
	// �巡�� ��� �� �߻��ϴ� �̺�Ʈ�Դϴ�.
	FSlotDragEvent OnSlotDragCancelled;


protected :
	// ������ Ÿ���� ��Ÿ���ϴ�.
	ESlotType SlotType;

	// ������ ���԰� �Բ� ���Ǵ� �ڵ带 ��Ÿ���ϴ�.
	/// - ������ �ڵ�, ��ų �ڵ�
	FName InCode;

	// �巡�� �۾��� ����ϴ����� ��Ÿ���ϴ�.
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

	// ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	/// - FReply : ������ �̺�Ʈ�� ��� ������� ó���Ǿ����� �˸��� ���� ����

	// ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonUp(
		const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;

	// �� ������ ���콺 ��ħ�� ���۵� ��� ȣ��˴ϴ�.
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// �� ������ ���콺 ��ħ�� ���� ��� ȣ��˴ϴ�.
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// �� �������� �巡�װ� ������ ��� ȣ��Ǵ� �޼���
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, 
		const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	/// - OutOperation : ��¿� �Ű� �����̸�, ������ �巡�� �۾� ��ü�� ��ȯ�մϴ�.

	// �巡�װ� ������ ��� ȣ��˴ϴ�.
	virtual bool NativeOnDrop(const FGeometry& InGeometry, 
		const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// �巡�� ��� �� ȣ��˴ϴ�.
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, 
		UDragDropOperation* InOperation) override;

public :
	// ������ �ʱ�ȭ�մϴ�.
	virtual void InitializeSlot(ESlotType slotType, FName inCode);

	// ���Կ� ǥ�õǴ� ���ڸ� �����մϴ�.
	/// - itemCount : ǥ�ý�ų ������ ������ �����մϴ�.
	/// - bVisibleBelowOne : 1 ������ ��� ���� ǥ�� ���θ� �����մϴ�.
	void SetSlotItemCount(int32 itemCount, bool bVisibleBelowOne = false);

protected :
	TTuple<UUserWidget*, class UImage *> CreateSlotDragWidget();
	/// - Ʃ��
	/// - ������ �̸��� ������ �ʰ�, ���� �ʵ带 ���� �� �ִ� ����ü�Դϴ�.
	/// - TTuple<Types...> �������� ������ �� ������, MakeTuple �� ���� �ϳ��� ��ü�� ������ �� �ֽ��ϴ�.
	/// - ������ Ʃ���� �ʵ忡�� Get<index>() �� ������ �� �ֽ��ϴ�.

private :
	// ���� ����� �⺻ �������� ǥ���մϴ�.
	void ShowSlotNormalColor();

	// ���� ����� ���콺 ��ħ �������� ǥ���մϴ�.
	void ShowSlotHoveredColor();
	
	// ���� ����� ���콺 ���� �������� ǥ���մϴ�.
	void ShowSlotPressedColor();

public :
	FORCEINLINE class UImage* GetSlotImage() const
	{ return Image_Slot; }

	FORCEINLINE class UTextBlock* GetCountText() const
	{ return Text_Count; }

	FORCEINLINE ESlotType GetSlotType() const
	{ return SlotType; }

};
