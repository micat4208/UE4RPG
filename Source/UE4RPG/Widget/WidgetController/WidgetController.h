#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Widget/ClosableWnd/MessageBoxWnd/MessageBoxWnd.h"

#include "Enum/InputModeType.h"
#include "Enum/MessageBoxButton.h"

#include "WidgetController.generated.h"

UCLASS()
class UE4RPG_API UWidgetController final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	TSubclassOf<class UMessageBoxWnd> BP_MessageBoxWnd;
	TSubclassOf<class UUserWidget> BP_MessageBoxBackground;

private :
	class ABasePlayerController* PlayerController;

	// 할당되어있는 Widget 객체들을 나타냅니다.
	/// - 창 객체는 추가되지 않습니다.
	TArray<UUserWidget*> AllocatedWidgets;

	// 할당되어있는 ClosableWnd 객체들을 나타냅니다.
	TArray<class UClosableWnd*> AllocatedWnds;

	// 닫힌 창들의 이전 위치를 저장합니다.
	TMap<FString, FVector2D> PrevClosedWndPositions;

	// 닫기 시 ResetInputMode() 에서 닫힘 확인을 무시시킬 위젯들을 저장합니다.
	TArray<class UUserWidget* > IgnoreWidgets;
		

private :
	// 창 객체들이 아닌 HUD 가 추가될 캔버스
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WidgetParent;

	// 창 객체들이 추가될 캔버스
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WndParent;

public :
	UWidgetController(const FObjectInitializer& objIniter);

private :
	// 입력 모드, 커서 표시를 기본 값으로 초기화합니다.
	/// - 열린 위젯이나, 창이 존재한다면 입력 모드가 초기화되지 않습니다.
	/// - bForceChange : 열린 위젯이나, 창의 존재 여부를 무시하고 강제로 초기화시킬 것인지에 대한 여부를 전달합니다.
	void ResetInputMode(bool bForceChange = false);

	// 창의 위치를 저장합니다.
	void SaveWndPosition(const class UClosableWnd* closableWnd);

public :
	// Widget Controller 를 초기화합니다.
	void InitializeWidgetController(class ABasePlayerController* playerController);

	// 메시지 박스를 생성합니다.
	/// - titleText : 메시지 박스의 타이틀 문자열을 전달합니다.
	/// - msg : 메시지 박스의 내용을 전달합니다.
	/// - bUseBackground : 메시지 박스 후면에 배경이 깔리게 되도록 할 것인지를 결정합니다.
	/// - button : 표시될 버튼들을 나타냅니다.
	///   EMessageBoxButton::Type 을 OR 연산자와 함께 전달해야 합니다.
	///   ex) EMessageBoxButton::MB_OK | EMessageBoxButton::MB_Cancel
	FORCEINLINE class UMessageBoxWnd* CreateMessageBox(FString titleText, FString msg,
		bool bUseBackground = false, uint8 button = EMessageBoxButton::MB_Ok)
	{ return CreateMessageBox(FText::FromString(titleText), FText::FromString(msg), bUseBackground, button); }

	class UMessageBoxWnd* CreateMessageBox(FText titleText, FText msg, 
		bool bUseBackground = false, uint8 button = EMessageBoxButton::MB_Ok);

	// 하위 위젯을 추가합니다.
	/// - 추가된 위젯은 CanvasPanel_WidgetParent 캔버스 하위로 추가되며,
	///   창 위젯들보다 렌더, 상호작용 우선순위가 낮습니다.
	/// - childWidgetInstance : 추가할 하위 위젯 객체를 전달합니다.
	/// - bIgnoreThisWidget : 이 위젯을 ResetInputMode() 메서드 호출 시 닫힘을 확인하도록 할 것인지에 대한 여부를 전달합니다.
	/// - bShowMouseCursor : 창읠 띄운 후 커서를 표시할 것인지에 대한 여부를 전달합니다.
	/// - width : 띄운 위젯의 너비를 전달합니다.
	/// - height : 띄운 위젯의 높이를 전달합니다.
	void AddChildWidget(class UUserWidget* childWidgetInstance, 
		bool bIgnoreThisWidget = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// 추가시킨 하위 위젯을 닫습니다.
	/// - childWidgetInstance : 닫을 위젯 객체를 전달합니다.
	void CloseChildWidget(class UUserWidget* childWidgetInstance);

	// 창을 생성합니다.
	/// - wndClass : 생성할 창 UClass 를 전달합니다.
	/// - bUsePrevPosition : 창의 이전 위치 사용 여부를 전달합니다.
	/// - bIgnoreThisWidget : 이 위젯을 ResetInputMode() 메서드 호출 시 닫힘을 확인하도록 할 것인지에 대한 여부를 전달합니다.
	/// -  changeInputMode : 창을 띄운 후 변경할 입력 모드를 전달합니다.
	/// -  bShowMouseCursor : 커서 표시 여부를 전달합니다.
	/// -  alignmentX : 정렬 기준점이 되는 X위치를 전달합니다.
	/// -  alignmentY : 정렬 기준점이 되는 Y위치를 전달합니다.
	/// -  anchorMinX : 배치 시 기준점이 되는 X위치
	/// -  anchorMinY : 배치 시 기준점이 되는 Y위치
	/// -  anchorMaxX : 배치 시 기준점이 되는 X위치
	/// -  anchorMaxY : 배치 시 기준점이 되는 Y위치
	class UClosableWnd* CreateWnd(TSubclassOf<class UClosableWnd> wndClass,
		bool bUsePrevPosition = false,
		bool bIgnoreThisWidget = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float alignmentX = 0.5f, float alignmentY = 0.5f,
		float anchorMinX = 0.5f, float anchorMinY = 0.5f,
		float anchorMaxX = 0.5f, float anchorMaxY = 0.5f);

	// 창을 닫습니다.
	/// - bAllClose : 모든 창을 닫도록 할 것인지에 대한 여부를 전달합니다.
	/// - closableWnd : 닫을 창을 전달합니다.
	///   만약 nullptr 가 전달된다면 마지막에 열었던 창이 닫힙니다.
	void CloseWnd(bool bAllClose = false, class UClosableWnd* closableWnd = nullptr);

public :
	// 그리드 패널의 요소들을 차례대로 정렬합니다.
	/// - gridPanelElem : 정렬시킬 그리드 패널 요소를 전달합니다.
	/// - maxColumnCount : 최대 행 개수를 전달합니다.
	/// - ref_currentColumnCount : 현재 행 번호를 전달합니다.
	///   전달한 변수는 메서드 내부에서 변경됩니다.
	static void SortGridPanelElem(
		class UUserWidget* gridPanelElem,
		int32 maxColumnCount,
		int32& ref_currentColumnCount);


	
};
