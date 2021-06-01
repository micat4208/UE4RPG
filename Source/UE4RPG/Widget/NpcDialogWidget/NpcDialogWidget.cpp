#include "NpcDialogWidget.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/BaseNpc/BaseNpc.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/NpcShopWnd/NpcShopWnd.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Struct/ShopInfo/ShopInfo.h"

UNpcDialogWidget::UNpcDialogWidget(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UNpcShopWnd> BP_NPC_SHOP_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/NpcShopWnd/BP_NpcShopWnd.BP_NpcShopWnd_C'"));
	if (BP_NPC_SHOP_WND.Succeeded()) BP_NpcShopWnd = BP_NPC_SHOP_WND.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SHOP_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ShopInfo.DT_ShopInfo'"));
	if (DT_SHOP_INFO.Succeeded()) DT_ShopInfo = DT_SHOP_INFO.Object;

	NpcShopWnd = nullptr;
}

void UNpcDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 이 위젯이 포커싱을 지원하도록 합니다.
	bIsFocusable = true;

	// 키보드 포커싱을 설정합니다.
	SetKeyboardFocus();

	Button_Exit->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnExitButtonClicked);
	Button_Shop->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnShopButtonClicked);
	Button_Next->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnNextDialogButtonClicked);
}

FReply UNpcDialogWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// R 키 입력 시
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		// 다음 대화 내용을 표시합니다.
		OnNextDialogButtonClicked();
		return FReply::Handled();
	}
	else return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
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

void UNpcDialogWidget::OnShopButtonClicked()
{
	if (IsValid(NpcShopWnd)) return;

	// 상점 정보를 얻습니다.
	FString contextString;
	FShopInfo* shopInfo = DT_ShopInfo->FindRow<FShopInfo>(
		ConnectedNpc->GetNpcInfo()->ShopCode, contextString);

	NpcShopWnd = Cast<UNpcShopWnd>(
		GetManager(UPlayerManager)->GetPlayerController()->GetWidgetController()->
		CreateWnd(BP_NpcShopWnd, true));

	// Npc 상점 창 초기화
	NpcShopWnd->InitializeNpcShop(shopInfo);

	// 상점 창 닫힘 이벤트 설정
	NpcShopWnd->OnWndClosed.AddLambda([this]() { NpcShopWnd = nullptr; });
}

void UNpcDialogWidget::OnExitButtonClicked()
{
	ABasePlayerController * playerController = GetManager(UPlayerManager)->GetPlayerController();

	// 이 위젯을 닫습니다.
	playerController->GetWidgetController()->CloseChildWidget(this);
}
