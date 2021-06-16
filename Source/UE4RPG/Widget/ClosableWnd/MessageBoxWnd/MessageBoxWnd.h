#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Enum/MessageBoxButton.h"

#include "MessageBoxWnd.generated.h"

DECLARE_EVENT(UMessageBoxWnd, FMsgBoxButtonEvent)

UCLASS()
class UE4RPG_API UMessageBoxWnd : public UClosableWnd
{
	GENERATED_BODY()

public :
	TMap<EMessageBoxButton::Type, FMsgBoxButtonEvent> MsgBoxButtonEvents;

	UUserWidget* MsgBoxBackground;

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Message;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Ok;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Cancel;


protected:
	virtual void NativeConstruct() override;

public :
	void InitializeMessageBox(FText titleText, FText message, uint8 button);
	
	virtual void CloseThisWnd() override;
	
private :
	// 버튼의 가시성을 설정합니다.
	/// - button : 설정시킬 버튼 객체를 전달합니다.
	/// - buttonType : 해당 버튼의 타입을 전달합니다.
	/// - visibility : 표시 여부를 담고 있는 데이터를 전달합니다.
	void SetButtonVisibility(class UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility);

private :
	UFUNCTION()
	void OnOkButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();

};
