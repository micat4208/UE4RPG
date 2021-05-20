#include "PlayerInteractComponent.h"

#include "Component/InteractableArea/InteractableAreaComponent.h"

UPlayerInteractComponent::UPlayerInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInteractComponent::AddInteractable(UInteractableAreaComponent* newInteractable)
{
	if (!InteractableComponents.Contains(newInteractable))
		InteractableComponents.Add(newInteractable);
}

void UPlayerInteractComponent::RemoveInteractable(UInteractableAreaComponent* removeInteractable)
{
	if (InteractableComponents.Contains(removeInteractable))
		InteractableComponents.Remove(removeInteractable);
}

void UPlayerInteractComponent::TryInteraction()
{
	// 상호작용 가능한 객체가 존재하지 않을 경우 실행 X
	if (InteractableComponents.Num() < 1) return;

	// 플레이어 캐릭터와 가장 가까운 객체와 상호작용을 시작합니다.
	InteractableComponents[0]->StartInteract();
}