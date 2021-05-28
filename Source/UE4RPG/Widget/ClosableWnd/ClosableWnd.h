#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWnd.generated.h"

UCLASS()
class UE4RPG_API UClosableWnd : 
	public UUserWidget
{
	GENERATED_BODY()

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
	// 이 창을 닫습니다.
	UFUNCTION()
	void CloseThisWnd();

	// 이 창의 CanvasPanelSlot 을 반환합니다.
	/// - 이 메서드는 항상 화면에 추가된 후 사용되어야 합니다.
	class UCanvasPanelSlot* GetCanvasPanelSlot() const;
	
};
