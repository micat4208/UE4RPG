#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetController.generated.h"

UCLASS()
class UE4RPG_API UWidgetController final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	class ABasePlayerController* PlayerController;

	// 할당되어있는 Widget 객체들을 나타냅니다.
	/// - 창 객체는 추가되지 않습니다.
	TArray<UUserWidget*> AllocatedWidgets;


private :
	// 창 객체들이 아닌 HUD 가 추가될 캔버스
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WidgetParent;

	// 창 객체들이 추가될 캔버스
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WndParent;

public :
	// Widget Controller 를 초기화합니다.
	void InitializeWidgetController(class ABasePlayerController* playerController);

	// 하위 위젯을 추가합니다.
	/// - 추가된 위젯은 CanvasPanel_WidgetParent 캔버스 하위로 추가되며,
	///   창 위젯들보다 렌더, 상호작용 우선순위가 낮습니다.
	/// - childWidgetInstance : 추가할 하위 위젯 객체를 전달합니다.
	void AddChildWidget(class UUserWidget* childWidgetInstance);


	
};
