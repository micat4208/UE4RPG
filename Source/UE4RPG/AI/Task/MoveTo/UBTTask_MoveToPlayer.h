#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "UBTTask_MoveToPlayer.generated.h"

UCLASS()
class UE4RPG_API UUBTTask_MoveToPlayer : public UBTTask_MoveTo
{
	GENERATED_BODY()

public :
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory) override;
	
};
