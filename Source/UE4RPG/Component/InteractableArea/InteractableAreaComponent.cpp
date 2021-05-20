#include "InteractableAreaComponent.h"

#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Component/PlayerInteract/PlayerInteractComponent.h"


void UInteractableAreaComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractableAreaComponent::OnPlayerCharacterDetected);
	OnComponentEndOverlap.AddDynamic(this, &UInteractableAreaComponent::OnPlayerCharacterLost);

}

void UInteractableAreaComponent::StartInteract()
{
	OnInteractStarted.Broadcast(this);

	LOG(TEXT("StartInteract()!"));
}

void UInteractableAreaComponent::OnPlayerCharacterDetected(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	/// 겹친 액터가 PLAYER_ACTOR_TAG 와 일치하는 Tag 갖지 않는다면 플레이어 캐릭터가 아니므로 실행 X
	if (!OtherActor->ActorHasTag(PLAYER_ACTOR_TAG)) return;

	// 캐릭터 액터를 얻습니다.
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);

	// 자신을 상호작용 가능한 객체로 추가합니다.
	playerCharacter->GetPlayerInteract()->AddInteractable(this);
}

void UInteractableAreaComponent::OnPlayerCharacterLost(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	/// 겹친 액터가 PLAYER_ACTOR_TAG 와 일치하는 Tag 갖지 않는다면 플레이어 캐릭터가 아니므로 실행 X
	if (!OtherActor->ActorHasTag(PLAYER_ACTOR_TAG)) return;

	// 캐릭터 액터를 얻습니다.
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);

	// 자신을 상호작용 불가능 상태로 만듭니다.
	playerCharacter->GetPlayerInteract()->RemoveInteractable(this);
}
