#pragma once

#include "UE4RPG.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

UCLASS(Abstract)
class UE4RPG_API ABasePlayerController : 
	public APlayerController
{
	GENERATED_BODY()

private :
	TSubclassOf<class UWidgetController> BP_WidgetController;

private :
	class UWidgetController* WidgetController;

public :
	ABasePlayerController();

protected :
	virtual void OnPossess(APawn* aPawn) override;

public :
	FORCEINLINE class UWidgetController* GetWidgetController() const
	{ return WidgetController; }

	
};
