#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWnd.generated.h"

DECLARE_MULTICAST_DELEGATE(FWndEventSignature)

UCLASS()
class UE4RPG_API UClosableWnd : 
	public UUserWidget
{
	GENERATED_BODY()

public :
	// 창이 닫힐 때 발생하는 이벤트
	FWndEventSignature OnWndClosed;

public :
	// Widget Controller
	class UWidgetController* WidgetController;

public :
	// 창 크기를 나타냅니다.
	FVector2D WndSize;

	// 닫힘 처리된 창임을 나타냅니다.
	bool bBeClose;

private :
	UPROPERTY(meta = (BindWidget))
	class UDraggableWndTitle * DraggableWndTitle;

protected :
	virtual void NativeConstruct() override;

public :
	// 창의 제목을 설정합니다.
	void SetTitleText(FText newTitleText);

	FORCEINLINE void SetTielText(FString newTitleText)
	{ SetTitleText(FText::FromString(newTitleText)); }

	// 이 창을 닫습니다.
	UFUNCTION()
	virtual void CloseThisWnd();

	// 이 창의 CanvasPanelSlot 을 반환합니다.
	/// - 이 메서드는 항상 화면에 추가된 후 사용되어야 합니다.
	class UCanvasPanelSlot* GetCanvasPanelSlot() const;
	
};
