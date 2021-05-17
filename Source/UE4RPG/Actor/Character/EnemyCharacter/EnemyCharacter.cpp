#include "EnemyCharacter.h"

#include "Actor/Controller/EnemyController/EnemyController.h"

#include "Single/GameInstance/RPGGameInstance.h"

#include "Engine/DataTable.h"

#include "BehaviorTree/BehaviorTree.h"


AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_EnemyInfo.DT_EnemyInfo'"));
	if (DT_ENEMY_INFO.Succeeded()) DT_EnemyInfo = DT_ENEMY_INFO.Object;

	EnemyCode = FName(TEXT("1000"));

	// ����ϴ� AI Controller �� �����մϴ�.
	AIControllerClass = AEnemyController::StaticClass();

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeEnemyCharacter();

}

void AEnemyCharacter::InitializeEnemyCharacter()
{

	// �� �ڵ带 �̿��Ͽ� �� ������ ����ϴ�.
	FString contextString;
	EnemyInfo = DT_EnemyInfo->FindRow<FEnemyInfo>(EnemyCode, contextString);

	if (EnemyInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter.cpp :: %d LINE :: EnemyInfo is null (EnemyCode = %s)"),
			__LINE__, *EnemyCode.ToString());
		return;
	}

	
	// ���̷�Ż �޽� ����
	USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo->SkeletalMeshPath));
	/// - LoadSynchronous(target) : target �� �ش��ϴ� �ּ��� ���� ������� �ε��Ͽ� UObject* �������� ��ȯ�մϴ�.

	GetMesh()->SetSkeletalMesh(skeletalMesh);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// BehaviorTree ����
	BehaviorTree = Cast<UBehaviorTree>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo->UseBehaviorTreeAssetPath));

	// �ִ� �ν��Ͻ� Ŭ���� ����
	GetMesh()->SetAnimInstanceClass(EnemyInfo->AnimClass);

	// Behavior Tree Run!
	if (IsValid(BehaviorTree))
	{
		LOG(TEXT("IsValid(BehaviorTree)"));
		Cast<AEnemyController>(GetController())->RunBehaviorTree(BehaviorTree);
	}
}
