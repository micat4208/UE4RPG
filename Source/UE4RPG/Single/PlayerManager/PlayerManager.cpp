#include "PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"

void UPlayerManager::RegisterPlayer(
	ABasePlayerController* newPlayerController,
	APlayerCharacter* newPlayerCharacter)
{
	PlayerController = newPlayerController;
	(PlayerCharacter = newPlayerCharacter)->Tags.Add(PLAYER_ACTOR_TAG);

}
