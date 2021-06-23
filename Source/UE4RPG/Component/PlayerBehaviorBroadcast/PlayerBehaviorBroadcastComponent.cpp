#include "PlayerBehaviorBroadcastComponent.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

using namespace EPlayerBehavior;

UPlayerBehaviorBroadcastComponent::UPlayerBehaviorBroadcastComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	if (PlayerBehaviorEvents.Num() > 0) PlayerBehaviorEvents.Empty();
	PlayerBehaviorEvents.Add(BH_None, FPlayerBehaviorEvent());
	PlayerBehaviorEvents.Add(BH_UseInventoryItem, FPlayerBehaviorEvent());
}

void UPlayerBehaviorBroadcastComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �ൿ�� ����ִٸ� �������� �ʽ��ϴ�.
	if (PlayerBehaviors.IsEmpty()) return;

	// �߰��� �ൿ�� ����ϴ�.
	FPlayerBehaviorData newBehavior;
	PlayerBehaviors.Dequeue(newBehavior);

	// �߻��� �ൿ Ÿ�Կ� ���� �̺�Ʈ�� �߻���ŵ�ϴ�.
	PlayerBehaviorEvents[newBehavior.Behavior].Broadcast(newBehavior);
}

void UPlayerBehaviorBroadcastComponent::AddBehavior(FPlayerBehaviorData newBHData)
{
	PlayerBehaviors.Enqueue(newBHData);
}

void UPlayerBehaviorBroadcastComponent::UseInventoryItem(int32 inventorySlotIndex, int32 useCount)
{
	// inventorySlotIndex �� �ش��ϴ� �κ��丮 ���� ������ ����ϴ�.
	FItemSlotInfo& itemSlotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[inventorySlotIndex];

	FPlayerBehaviorData bhData(BH_UseInventoryItem, itemSlotInfo.ItemCode, useCount, inventorySlotIndex);
	AddBehavior(bhData);
}

