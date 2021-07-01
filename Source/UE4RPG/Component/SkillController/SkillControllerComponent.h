#pragma once

#include "UE4RPG.h"
#include "Components/ActorComponent.h"

#include "Struct/SkillInfo/SkillInfo.h"

#include "SkillControllerComponent.generated.h"


UCLASS()
class UE4RPG_API USkillControllerComponent : public UActorComponent
{
	GENERATED_BODY()

private :
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

private :
	// 스킬을 순서대로 처리합니다.
	void SkillProcedure();

	// 스킬을 시전합니다.
	void CastSkill(FSkillInfo* skillInfo);
		
};
