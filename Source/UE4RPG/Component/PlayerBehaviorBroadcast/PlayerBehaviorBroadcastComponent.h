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
	// Ư���� �ൿ�� ���� �� �߻��ϴ� �̺�Ʈ���� ��Ÿ���ϴ�.
	TMap<EPlayerBehavior::Type, FPlayerBehaviorEvent> PlayerBehaviorEvents;

	// �߻��� �ൿ �����Ͱ� ����˴ϴ�.
	TQueue<FPlayerBehaviorData> PlayerBehaviors;

public:	
	UPlayerBehaviorBroadcastComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// �ൿ�� �߰��մϴ�.
	/// - newBHData : �ൿ �����Ͱ� ���޵˴ϴ�.
	void AddBehavior(FPlayerBehaviorData newBHData);

	// �κ��丮 �������� ����մϴ�.
	/// - inventorySlotIndex : ���� �κ��丮 ������ �����մϴ�.
	/// - useCount : ��� ������ �����մϴ�.
	void UseInventoryItem(int32 inventorySlotIndex, int32 useCount = 1);



};
