#pragma once

#include "CoreMinimal.h"

#include "Single/PlayerManager/PlayerInventory/PlayerInventory.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "PlayerManager.generated.h"

#ifndef PLAYER_ACTOR_TAG
#define PLAYER_ACTOR_TAG	TEXT("PlayerCharacter")
#endif


UCLASS()
class UE4RPG_API UPlayerManager final : 
	public UManagerClass
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class UPlayerInventory* PlayerInventory;

	UPROPERTY()
	class ABasePlayerController* PlayerController;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public :
	// 플레이어 컨트롤러와 캐릭터를 등록합니다.
	void RegisterPlayer(class ABasePlayerController* newPlayerController,
		class APlayerCharacter* newPlayerCharacter);

	virtual void InitManagerClass() override;
	virtual void ShutdownManagerClass() override;

public :
	FORCEINLINE class UPlayerInventory* GetPlayerInventory() const
	{ return PlayerInventory; }

	FORCEINLINE class ABasePlayerController* GetPlayerController() const
	{ return PlayerController; }

	FORCEINLINE class APlayerCharacter* GetPlayerCharacter() const
	{ return PlayerCharacter; }
};
