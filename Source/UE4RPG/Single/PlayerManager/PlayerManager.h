#pragma once

#include "CoreMinimal.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "PlayerManager.generated.h"

UCLASS()
class UE4RPG_API UPlayerManager final : 
	public UManagerClass
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class ABasePlayerController* PlayerController;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public :
	// 플레이어 컨트롤러와 캐릭터를 등록합니다.
	void RegisterPlayer(class ABasePlayerController* newPlayerController,
		class APlayerCharacter* newPlayerCharacter);

public :
	FORCEINLINE class ABasePlayerController* GetPlayerController() const
	{ return PlayerController; }

	FORCEINLINE class APlayerCharacter* GetPlayerCharacter() const
	{ return PlayerCharacter; }
};
