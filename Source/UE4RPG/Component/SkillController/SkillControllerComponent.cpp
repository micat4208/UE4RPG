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

	// ��ų�� ������� �����ŵ�ϴ�.
	SkillProcedure();
}

void USkillControllerComponent::SkillProcedure()
{
	// ���� �������� ��ų�� �����Ѵٸ� ���� X
	/// - ��ų�� ���������� �ϳ��� ����ǵ��� �մϴ�.
	if (CurrentSkillInfo != nullptr) return;

	// ��û�� ��ų�� �������� �ʴ´ٸ� ���� X
	if (SkillQueue.IsEmpty()) return;

	// ������ �����ų ��ų ������ ����ϴ�.
	FSkillInfo* skillInfo = nullptr;
	SkillQueue.Dequeue(skillInfo);
	--SkillCount;

	// ��ų ����
	CastSkill(skillInfo);

}

void USkillControllerComponent::CastSkill(FSkillInfo* skillInfo)
{
}

