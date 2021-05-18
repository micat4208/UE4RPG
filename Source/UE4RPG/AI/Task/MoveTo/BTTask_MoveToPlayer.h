#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToPlayer.generated.h"

UCLASS()
class UE4RPG_API UBTTask_MoveToPlayer : public UBTTask_MoveTo
{
	GENERATED_BODY()

public :
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory) override;
	
};
