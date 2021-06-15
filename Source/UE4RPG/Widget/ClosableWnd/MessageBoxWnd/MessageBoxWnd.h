#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Enum/MessageBoxButton.h"

#include "MessageBoxWnd.generated.h"

UCLASS()
class UE4RPG_API UMessageBoxWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Message;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Ok;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Cancel;


public :
	void InitializeMessageBox(FText titleText, FText message, uint8 button);
	
private :
	// ��ư�� ���ü��� �����մϴ�.
	/// - button : ������ų ��ư ��ü�� �����մϴ�.
	/// - buttonType : �ش� ��ư�� Ÿ���� �����մϴ�.
	/// - visibility : ǥ�� ���θ� ��� �ִ� �����͸� �����մϴ�.
	void SetButtonVisibility(class UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility);

};
