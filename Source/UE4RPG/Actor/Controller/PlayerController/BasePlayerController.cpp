#include "BasePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

void ABasePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	GetManager(UPlayerManager)->RegisterPlayer(this, Cast<APlayerCharacter>(aPawn));
}