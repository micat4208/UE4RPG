#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWndTitle.generated.h"

UCLASS()
class UE4RPG_API UDraggableWndTitle final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	// 드래깅을 체크할 버튼
	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Draggable;

	// 닫기 버튼
	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Close;

	// 창 제목
	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Title;

	// 드래깅 중임을 나타냅니다.
	bool bIsDragging;
	
	// 드래깅 시킬 창 위젯을 나타냅니다.
	class UClosableWnd* TargetWnd;

	// 드래그 시작 위치를 나타냅니다.
	FVector2D DragStartPosition;

	// 드래그 시작 입력 마우스 위치를 나타냅니다.
	FVector2D DragInputPosition;
	
public :
	UDraggableWndTitle(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	FORCEINLINE void SetDragTarget(class UClosableWnd* targetWnd)
	{ TargetWnd = targetWnd; }

	FORCEINLINE class UButton* GetCloseButton() const
	{ return Button_Close; }

private :
	void DragWidget();

	UFUNCTION()
	void OnWidgetDragStarted();

	UFUNCTION()
	void OnWidgetDragFinished();

};
