#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

UCLASS()
class UE4RPG_API UPlayerHUD final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UProgressBar * ProgressBar_Hp;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar * ProgressBar_Mp;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Level;


protected :
	virtual void NativeConstruct() override;

};
