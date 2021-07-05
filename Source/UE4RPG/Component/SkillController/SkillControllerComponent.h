#pragma once

#include "UE4RPG.h"
#include "Components/ActorComponent.h"

#include "Struct/SkillInfo/SkillInfo.h"

#include "SkillControllerComponent.generated.h"

#ifndef MAX_SKILL_QUEUE_SIZE
#define MAX_SKILL_QUEUE_SIZE	2
#endif

UCLASS()
class UE4RPG_API USkillControllerComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	class UDataTable* DT_SkillInfo;

private :
	class APlayerCharacter* PlayerCharacter;

	// 실행중인 스킬 정보를 나타냅니다.
	FSkillInfo* CurrentSkillInfo;

	// 실행시킬 스킬들을 담아둘 큐
	TQueue<FSkillInfo*> SkillQueue;

	// 현재 실생시켜야 하는 스킬 개수를 나타냅니다.
	int32 SkillCount;

	// 스킬을 요청할 수 있음을 나타냅니다.
	/// - 이 값이 false 라면 스킬을 요청할 수 없습니다.
	bool bIsRequestable;

public:	
	USkillControllerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// 스킬 시전을 요청합니다.
	void RequestSkill(FName skillCode);

	// 스킬이 끝났음을 알립니다.
	void SkillFinished();

	// 스킬 범위를 생성합니다.
	void CreateSkillRange();

private :
	// 스킬을 순서대로 처리합니다.
	void SkillProcedure();

	// 스킬을 시전합니다.
	void CastSkill(FSkillInfo* skillInfo);
		
};
