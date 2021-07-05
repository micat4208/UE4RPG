#include "SkillControllerComponent.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

USkillControllerComponent::USkillControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SKILL_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_SkillInfo.DT_SkillInfo'"));
	if (DT_SKILL_INFO.Succeeded()) DT_SkillInfo = DT_SKILL_INFO.Object;

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

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

void USkillControllerComponent::RequestSkill(FName skillCode)
{
	// ��ų�� ��û�� �� ���� ��� ��ų ���� ��û�� ���� �ʽ��ϴ�.
	if (!bIsRequestable) return;

	// ��ų�� 2 �� �̻� ��ϵƴٸ� ��ų ���� ��û�� ���� �ʽ��ϴ�.
	if (SkillCount >= MAX_SKILL_QUEUE_SIZE) return;

	// ��û�� ��ų ������ ����ϴ�.
	FString contextString;
	FSkillInfo* requestSkillInfo = DT_SkillInfo->FindRow<FSkillInfo>(skillCode, contextString);

	// ��û�� ��ų ������ ã�� ���ߴٸ� ��û�� ���� �ʽ��ϴ�.
	if (requestSkillInfo == nullptr) return;

	// ��û�� ��ų�� ����� �Բ� ���Ǿ�� �ϴ� ��ų���� Ȯ���մϴ�.
	if (requestSkillInfo->bCanBeUsedWithWeapon &&

		// ���� ���Ⱑ �����Ǿ����� ���� ���¶��
		!GetManager(UPlayerManager)->GetPlayerInventory()->IsEquippedWeapon()) return;

	// �����ų ��ų�� ��� ť�� �߰��մϴ�.
	SkillQueue.Enqueue(requestSkillInfo);
	++SkillCount;
}

void USkillControllerComponent::SkillFinished()
{
	CurrentSkillInfo = nullptr;
	bIsRequestable = true;

}

void USkillControllerComponent::CreateSkillRange()
{
	if (!CurrentSkillInfo) return;

	FVector tracingStart = PlayerCharacter->GetActorLocation();
	FVector tracingEnd = tracingStart + (PlayerCharacter->GetActorForwardVector() * 200.0f);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(PlayerCharacter);

	// ���� ����� ������ �迭
	TArray<FHitResult> hitResults;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		tracingStart, tracingEnd,
		100.0f,
		FName(TEXT("PlayerSkill")),
		true,
		ActorsToIgnore, EDrawDebugTrace::ForDuration,
		hitResults,
		true);

	// ������ ��ü�� �����Ѵٸ�
	if (hitResults.Num() > 0)
	{
		for (FHitResult hit : hitResults)
		{
			// ������ ���Ͱ� ���̶��
			if (hit.Actor->ActorHasTag(TEXT("Enemy")))
			{
				// ����� ���ϱ�
				LOG(TEXT("Enemy!!"));
			}
		}
	}





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
	CurrentSkillInfo = skillInfo;

	bIsRequestable = false;

	PlayerCharacter->PlayAnimMontage(CurrentSkillInfo->AnimMontage);
}

