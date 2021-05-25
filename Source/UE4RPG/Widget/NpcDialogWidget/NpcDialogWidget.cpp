#include "NpcDialogWidget.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/BaseNpc/BaseNpc.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/WidgetController/WidgetController.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UNpcDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Exit->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnExitButtonClicked);

	Button_Next->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnNextDialogButtonClicked);
}

void UNpcDialogWidget::ShowDialog(int32 newDialogIndex)
{
	// ��ȭ ������ ����ִ��� Ȯ���մϴ�.
	if (DialogInfo.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("NpcDialogWidget.cpp :: %d LINE :: DialogInfo is Empty!"), __LINE__);
		return;
	}

	// ǥ�ý�ų ��ȭ �ε����� ������ ��ȭ �ε����� �ʰ��ϴ��� Ȯ���մϴ�.
	if (DialogInfo.GetLastDialogIndex() < newDialogIndex)
	{
		LOG(TEXT("NpcDialogWidget.cpp :: %d LINE :: [Warning] Out Of Range! newDialogIndex is Changed. (%d -> %d)"),
			__LINE__, newDialogIndex, DialogInfo.GetLastDialogIndex());

		newDialogIndex = DialogInfo.GetLastDialogIndex();
	}

	// ��ȭ ���� �ؽ�Ʈ ����
	Text_Dialog->SetText(DialogInfo.DialogText[newDialogIndex]);

	// ������ ��ȭ���
	bIsLastDialog = (DialogInfo.GetLastDialogIndex() == newDialogIndex);

	// ������ ��ȭ��� Next ��ư�� ����ϴ�.
	if (bIsLastDialog)
	{
		SetButtonVisibility(Button_Next, false);
	}

	// ������ ��ȭ�� �ƴ��ϸ� Next ��ư�� ǥ���մϴ�.
	else SetButtonVisibility(Button_Next, true);
}

void UNpcDialogWidget::SetButtonVisibility(UButton* button, bool bVisible)
{
	button->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UNpcDialogWidget::InitializeDialog()
{
	FNpcInfo* npcInfo = ConnectedNpc->GetNpcInfo();

	if (npcInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NpcDialogWidget.cpp :: %d LINE :: npcInfo is nullptr!"), __LINE__);
		return;
	}

	bIsLastDialog = false;

	// Npc �̸� ����
	Text_NpcName->SetText(npcInfo->NpcName);

	// ��ȭ ������ �⺻ ��ȭ �������� �����մϴ�.
	DialogInfo = npcInfo->DefaultDialogInfo;

	// ��ȭ ������ ó������ �ǵ����ϴ�.
	CurrentDialogIndex = 0;

	// ��ȭ ���� ǥ��
	ShowDialog(CurrentDialogIndex);
}

void UNpcDialogWidget::OnNextDialogButtonClicked()
{
	ShowDialog(++CurrentDialogIndex);
}

void UNpcDialogWidget::OnExitButtonClicked()
{
	ABasePlayerController * playerController = GetManager(UPlayerManager)->GetPlayerController();

	// �� ������ �ݽ��ϴ�.
	playerController->GetWidgetController()->CloseChildWidget(this);
}
