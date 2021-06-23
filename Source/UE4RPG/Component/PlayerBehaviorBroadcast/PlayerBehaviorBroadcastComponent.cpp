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

	// 행동이 비어있다면 실행하지 않습니다.
	if (PlayerBehaviors.IsEmpty()) return;

	// 추가된 행동을 얻습니다.
	FPlayerBehaviorData newBehavior;
	PlayerBehaviors.Dequeue(newBehavior);

	// 발생한 행동 타입에 따라 이벤트를 발생시킵니다.
	PlayerBehaviorEvents[newBehavior.Behavior].Broadcast(newBehavior);
}

void UPlayerBehaviorBroadcastComponent::AddBehavior(FPlayerBehaviorData newBHData)
{
	PlayerBehaviors.Enqueue(newBHData);
}

void UPlayerBehaviorBroadcastComponent::UseInventoryItem(int32 inventorySlotIndex, int32 useCount)
{
	// inventorySlotIndex 에 해당하는 인벤토리 슬롯 정보를 얻습니다.
	FItemSlotInfo& itemSlotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[inventorySlotIndex];

	FPlayerBehaviorData bhData(BH_UseInventoryItem, itemSlotInfo.ItemCode, useCount, inventorySlotIndex);
	AddBehavior(bhData);
}

