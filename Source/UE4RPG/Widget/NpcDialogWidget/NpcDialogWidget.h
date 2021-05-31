#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"
#include "Struct/NpcDialogInfo/NpcDialogInfo.h"
#include "NpcDialogWidget.generated.h"

UCLASS()
class UE4RPG_API UNpcDialogWidget final : 
	public UUserWidget
{
	GENERATED_BODY()

public :
	class ABaseNpc* ConnectedNpc;
	TSubclassOf<class UNpcShopWnd> BP_NpcShopWnd;

private :
	// 표시되는 대화 정보를 나타냅니다.
	FNpcDialogInfo DialogInfo;

	// 현재 표시되는 대화 내용 인덱스를 나타냅니다.
	int32 CurrentDialogIndex;

	// 마지막 대화임을 나타냅니다.
	bool bIsLastDialog;

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_NpcName;

#pragma region Button Panel

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_GoToFirst;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Quest;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Shop;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

#pragma endregion




#pragma region Dialog Panel

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Dialog;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Next;

#pragma endregion

public :
	UNpcDialogWidget(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private :
	// 지정한 순서의 대화를 표시합니다.
	void ShowDialog(int32 newDialogIndex);

	void SetButtonVisibility(class UButton* button, bool bVisible);


#pragma region Button Events

public :
	void InitializeDialog();

private :
	UFUNCTION()
	void OnNextDialogButtonClicked();

	UFUNCTION()
	void OnShopButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

#pragma endregion


	
};
