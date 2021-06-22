#pragma once

#include "UE4RPG.h"
#include "GameFramework/PlayerController.h"

#include "Enum/InputModeType.h"
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
	class UPlayerBehaviorBroadcastComponent* PlayerBehaviorBroadcast;

protected :
	// 기본 입력 모드를 나타냅니다.
	EInputModeType DefaultInputMode;

	// 기본 커서 가시성을 나타냅니다.
	bool bDefaultCursotVisibility;

public :
	ABasePlayerController();

protected :
	virtual void OnPossess(APawn* aPawn) override;

public :
	FORCEINLINE class UWidgetController* GetWidgetController() const
	{ return WidgetController; }

	FORCEINLINE class UPlayerBehaviorBroadcastComponent* GetPlayerBehaviorBroadcast() const
	{ return PlayerBehaviorBroadcast; }

	FORCEINLINE bool GetDefaultCursotVisibility() const
	{ return bDefaultCursotVisibility; }

	FORCEINLINE void SetInputModeFromNewInputModeType(EInputModeType newInputMode)
	{
		switch (newInputMode)
		{
		case EInputModeType::IM_GameOnly:  SetInputMode(FInputModeGameOnly());  break;
		case EInputModeType::IM_UIOnly:    SetInputMode(FInputModeUIOnly());	break;
		case EInputModeType::IM_GameAndUI: SetInputMode(FInputModeGameAndUI());	break;
		}
	}

	FORCEINLINE void ChangeInputModeToDefault()
	{ SetInputModeFromNewInputModeType(DefaultInputMode); }

	
};
