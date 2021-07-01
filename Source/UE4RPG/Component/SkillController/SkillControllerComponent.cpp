#include "SkillControllerComponent.h"

USkillControllerComponent::USkillControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentSkillInfo = nullptr;
	SkillCount = 0;
	bIsRequestable = true;

}

void USkillControllerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USkillControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 스킬을 순서대로 실행시킵니다.
	SkillProcedure();
}

void USkillControllerComponent::SkillProcedure()
{
	// 현재 실행중인 스킬이 존재한다면 실행 X
	/// - 스킬은 순차적으로 하나씩 진행되도록 합니다.
	if (CurrentSkillInfo != nullptr) return;

	// 요청된 스킬이 존재하지 않는다면 실행 X
	if (SkillQueue.IsEmpty()) return;

	// 다음에 실행시킬 스킬 정보를 얻습니다.
	FSkillInfo* skillInfo = nullptr;
	SkillQueue.Dequeue(skillInfo);
	--SkillCount;

	// 스킬 시전
	CastSkill(skillInfo);

}

void USkillControllerComponent::CastSkill(FSkillInfo* skillInfo)
{
}

