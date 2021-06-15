#include "MessageBoxWnd.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

using namespace EMessageBoxButton;

void UMessageBoxWnd::InitializeMessageBox(FText titleText, FText message, uint8 button)
{
	// �޽��� �ڽ� ���� ����
	SetTitleText(titleText);

	// ���� ����
	Text_Message->SetText(message);

	SetButtonVisibility(Button_Ok, MB_Ok, button);
	SetButtonVisibility(Button_Cancel, MB_Cancel, button);
}

void UMessageBoxWnd::SetButtonVisibility(UButton* button, EMessageBoxButton::Type buttonType, uint8 visibility)
{
	ESlateVisibility visible = ESlateVisibility::Visible;
	ESlateVisibility hide = ESlateVisibility::Collapsed;

	button->SetVisibility( (((uint8)buttonType & visibility) == 0) ? hide : visible);
}
