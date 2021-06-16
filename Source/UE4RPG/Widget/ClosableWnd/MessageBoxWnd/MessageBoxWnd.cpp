#include "MessageBoxWnd.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

using namespace EMessageBoxButton;

void UMessageBoxWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(500.0f, 300.0f);

	MsgBoxBackground = nullptr;

	MsgBoxButtonEvents.Add(MB_Ok, FMsgBoxButtonEvent());
	MsgBoxButtonEvents.Add(MB_Cancel, FMsgBoxButtonEvent());
}

void UMessageBoxWnd::InitializeMessageBox(FText titleText, FText message, uint8 button)
{
	// 메시지 박스 제목 설정
	SetTitleText(titleText);

	// 내용 설정
	Text_Message->SetText(message);

	SetButtonVisibility(Button_Ok, MB_Ok, button);
	SetButtonVisibility(Button_Cancel, MB_Cancel, button);

	Button_Ok->OnClicked.AddDynamic(this, &ThisClass::OnOkButtonClicked);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::OnCancelButtonClicked);
}

void UMessageBoxWnd::CloseThisWnd()
{
	if (IsValid(MsgBoxBackground))
	{
		MsgBoxBackground->RemoveFromParent();
		MsgBoxBackground = nullptr;
	}

	Super::CloseThisWnd();
}

void UMessageBoxWnd::SetButtonVisibility(UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility)
{
	ESlateVisibility visible = ESlateVisibility::Visible;
	ESlateVisibility hide = ESlateVisibility::Collapsed;

	button->SetVisibility( (((uint8)buttonType & visibility) == 0) ? hide : visible);
}

void UMessageBoxWnd::OnOkButtonClicked()
{
	MsgBoxButtonEvents[MB_Ok].Broadcast();

	CloseThisWnd();
}

void UMessageBoxWnd::OnCancelButtonClicked()
{
	MsgBoxButtonEvents[MB_Cancel].Broadcast();

	CloseThisWnd();
}
