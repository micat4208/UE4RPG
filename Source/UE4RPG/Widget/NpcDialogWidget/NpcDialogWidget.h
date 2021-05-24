#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcDialogWidget.generated.h"

UCLASS()
class UE4RPG_API UNpcDialogWidget final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
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

protected :
	virtual void NativeConstruct() override;

#pragma region Button Events

private :
	UFUNCTION()
	void OnExitButtonClicked();

#pragma endregion
	
};
