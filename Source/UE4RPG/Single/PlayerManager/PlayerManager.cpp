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

void UPlayerManager::InitializePlayerCharacter()
{
	// 모든 파츠 비우기
	GetPlayerCharacter()->ClearAllPartsMesh();

	// 비쥬얼 갱신


}

void UPlayerManager::InitManagerClass()
{
	PlayerInventory = NewObject<UPlayerInventory>(this, UPlayerInventory::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
}

void UPlayerManager::ShutdownManagerClass()
{
	// Release PlayerInventory
	// 해당 객체가 GC 에 의해 해제된 객체인지 확인
	if (!PlayerInventory->IsValidLowLevel()) return;

	// 아니라면 객체 소멸
	PlayerInventory->ConditionalBeginDestroy();
	PlayerInventory = nullptr;
}
