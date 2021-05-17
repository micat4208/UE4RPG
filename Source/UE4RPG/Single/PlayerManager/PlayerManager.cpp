#include "PlayerManager.h"

void UPlayerManager::RegisterPlayer(
	ABasePlayerController* newPlayerController,
	APlayerCharacter* newPlayerCharacter)
{
	PlayerController = newPlayerController;
	PlayerCharacter = newPlayerCharacter;
}
