#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Struct/PlayerBehaviorData/PlayerBehaviorData.h"

#include "PlayerBehaviorBroadcastComponent.generated.h"


DECLARE_EVENT_OneParam(UPlayerBehaviorBroadcastComponent, FPlayerBehaviorEvent, FPlayerBehaviorData&)

UCLASS()
class UE4RPG_API UPlayerBehaviorBroadcastComponent final : 
	public UActorComponent
{
	GENERATED_BODY()

private :
	// 특정한 행동을 했을 때 발생하는 이벤트들을 나타냅니다.
	TMap<EPlayerBehavior::Type, FPlayerBehaviorEvent> PlayerBehaviorEvents;

	// 발생한 행동 데이터가 저장됩니다.
	TQueue<FPlayerBehaviorData> PlayerBehaviors;

public:	
	UPlayerBehaviorBroadcastComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// 행동을 추가합니다.
	/// - newBHData : 행동 데이터가 전달됩니다.
	void AddBehavior(FPlayerBehaviorData newBHData);

	// 인벤토리 아이템을 사용합니다.
	/// - inventorySlotIndex : 사용된 인벤토리 슬롯을 전달합니다.
	/// - useCount : 사용 개수를 전달합니다.
	void UseInventoryItem(int32 inventorySlotIndex, int32 useCount = 1);



};
