#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enum/InputModeType.h"

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

private :
	// 입력 모드, 커서 표시를 기본 값으로 초기화합니다.
	/// - 열린 위젯이나, 창이 존재한다면 입력 모드가 초기화되지 않습니다.
	/// - bForceChange : 열린 위젯이나, 창의 존재 여부를 무시하고 강제로 초기화시킬 것인지에 대한 여부를 전달합니다.
	void ResetInputMode(bool bForceChange = false);

public :
	// Widget Controller 를 초기화합니다.
	void InitializeWidgetController(class ABasePlayerController* playerController);

	// 하위 위젯을 추가합니다.
	/// - 추가된 위젯은 CanvasPanel_WidgetParent 캔버스 하위로 추가되며,
	///   창 위젯들보다 렌더, 상호작용 우선순위가 낮습니다.
	/// - childWidgetInstance : 추가할 하위 위젯 객체를 전달합니다.
	/// - bShowMouseCursor : 창읠 띄운 후 커서를 표시할 것인지에 대한 여부를 전달합니다.
	/// - width : 띄운 위젯의 너비를 전달합니다.
	/// - height : 띄운 위젯의 높이를 전달합니다.
	void AddChildWidget(class UUserWidget* childWidgetInstance, 
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// 추가시킨 하위 위젯을 닫습니다.
	/// - childWidgetInstance : 닫을 위젯 객체를 전달합니다.
	void CloseChildWidget(class UUserWidget* childWidgetInstance);


	
};
