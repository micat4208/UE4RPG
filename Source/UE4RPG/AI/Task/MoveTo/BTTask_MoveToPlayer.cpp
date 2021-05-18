#include "BTTask_MoveToPlayer.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Controller/EnemyController/EnemyController.h"
#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

using namespace EBTNodeResult;

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(
	UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComponent, nodeMemory);


	// 적 캐릭터 컨트롤러를 얻습니다.
	AEnemyController* enemyController = Cast<AEnemyController>(ownerComponent.GetAIOwner());
	/// - ownerComponent : 이 행동을 사용하는 BehaviorTreeComponnet 를 나타냅니다.
	/// - UBehaviorTreeComponent->GetAIOwner() : 이 BehaviorTreeComponent 를 사용중인 AIContyroller 객체를 반환합니다.

	// 플레이어 캐릭터 위치를 목표 위치로 설정하기 위하여 플레이어 캐릭터를 얻습니다.
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerCharacter());

	// Blackboard 에 추가된 키(TargetPosition) 의 값을 플레이어 캐릭터의 위치로 설정합니다.
	enemyController->GetBlackboardComponent()->SetValueAsVector(
		FName(TEXT("TargetPosition")),
		playerCharacter->GetActorLocation());


	LOG(TEXT("TargetPositiop = %s"), 
		*enemyController->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("TargetPosition"))).ToString());

	// 행동 성공
	return Succeeded;
}