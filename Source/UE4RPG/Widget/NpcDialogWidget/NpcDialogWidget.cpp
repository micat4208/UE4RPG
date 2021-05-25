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
	// 대화 내용이 비어있는지 확인합니다.
	if (DialogInfo.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("NpcDialogWidget.cpp :: %d LINE :: DialogInfo is Empty!"), __LINE__);
		return;
	}

	// 표시시킬 대화 인덱스가 마지막 대화 인덱스를 초과하는지 확인합니다.
	if (DialogInfo.GetLastDialogIndex() < newDialogIndex)
	{
		LOG(TEXT("NpcDialogWidget.cpp :: %d LINE :: [Warning] Out Of Range! newDialogIndex is Changed. (%d -> %d)"),
			__LINE__, newDialogIndex, DialogInfo.GetLastDialogIndex());

		newDialogIndex = DialogInfo.GetLastDialogIndex();
	}

	// 대화 내용 텍스트 설정
	Text_Dialog->SetText(DialogInfo.DialogText[newDialogIndex]);

	// 마지막 대화라면
	bIsLastDialog = (DialogInfo.GetLastDialogIndex() == newDialogIndex);

	// 마지막 대화라면 Next 버튼을 숨깁니다.
	if (bIsLastDialog)
	{
		SetButtonVisibility(Button_Next, false);
	}

	// 마지막 대화가 아니하면 Next 버튼을 표시합니다.
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

	// Npc 이름 설정
	Text_NpcName->SetText(npcInfo->NpcName);

	// 대화 내용을 기본 대화 내용으로 설정합니다.
	DialogInfo = npcInfo->DefaultDialogInfo;

	// 대화 순서를 처음으로 되돌립니다.
	CurrentDialogIndex = 0;

	// 대화 내용 표시
	ShowDialog(CurrentDialogIndex);
}

void UNpcDialogWidget::OnNextDialogButtonClicked()
{
	ShowDialog(++CurrentDialogIndex);
}

void UNpcDialogWidget::OnExitButtonClicked()
{
	ABasePlayerController * playerController = GetManager(UPlayerManager)->GetPlayerController();

	// 이 위젯을 닫습니다.
	playerController->GetWidgetController()->CloseChildWidget(this);
}
