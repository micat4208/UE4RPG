#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWnd.generated.h"

UCLASS()
class UE4RPG_API UClosableWnd : 
	public UUserWidget
{
	GENERATED_BODY()


private :
	UPROPERTY(meta = (BindWidget))
	class UDraggableWndTitle * DraggableWndTitle;

protected :
	virtual void NativeConstruct() override;
	
};
