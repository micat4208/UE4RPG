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
	// ��ư�� ���ü��� �����մϴ�.
	/// - button : ������ų ��ư ��ü�� �����մϴ�.
	/// - buttonType : �ش� ��ư�� Ÿ���� �����մϴ�.
	/// - visibility : ǥ�� ���θ� ��� �ִ� �����͸� �����մϴ�.
	void SetButtonVisibility(class UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility);

private :
	UFUNCTION()
	void OnOkButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();

};
