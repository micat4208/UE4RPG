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

	// 스킬을 순서대로 실행시킵니다.
	SkillProcedure();
}

void USkillControllerComponent::RequestSkill(FName skillCode)
{
	// 스킬을 요청할 수 없는 경우 스킬 시전 요청을 받지 않습니다.
	if (!bIsRequestable) return;

	// 스킬이 2 개 이상 등록됐다면 스킬 시전 요청을 받지 않습니다.
	if (SkillCount >= MAX_SKILL_QUEUE_SIZE) return;

	// 요청한 스킬 정보를 얻습니다.
	FString contextString;
	FSkillInfo* requestSkillInfo = DT_SkillInfo->FindRow<FSkillInfo>(skillCode, contextString);

	// 요청한 스킬 정보를 찾지 못했다면 요청을 받지 않습니다.
	if (requestSkillInfo == nullptr) return;

	// 요청한 스킬이 무기와 함께 사용되어야 하는 스킬인지 확인합니다.
	if (requestSkillInfo->bCanBeUsedWithWeapon &&

		// 현재 무기가 장착되어있지 않은 상태라면
		!GetManager(UPlayerManager)->GetPlayerInventory()->IsEquippedWeapon()) return;

	// 실행시킬 스킬을 담는 큐에 추가합니다.
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

	// 감지 결과를 저장할 배열
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

	// 감지된 객체가 존재한다면
	if (hitResults.Num() > 0)
	{
		for (FHitResult hit : hitResults)
		{
			// 감지된 액터가 적이라면
			if (hit.Actor->ActorHasTag(TEXT("Enemy")))
			{
				// 대미지 가하기
				LOG(TEXT("Enemy!!"));
			}
		}
	}





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
	CurrentSkillInfo = skillInfo;

	bIsRequestable = false;

	PlayerCharacter->PlayAnimMontage(CurrentSkillInfo->AnimMontage);
}

