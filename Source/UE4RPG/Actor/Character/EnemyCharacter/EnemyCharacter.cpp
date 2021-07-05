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

	// 사용하는 AI Controller 를 설정합니다.
	AIControllerClass = AEnemyController::StaticClass();

	// Collision Presets 의 값을 설정합니다.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCharacter"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeEnemyCharacter();

	Tags.Add(TEXT("Enemy"));
}

void AEnemyCharacter::InitializeEnemyCharacter()
{

	// 적 코드를 이용하여 적 정보를 얻습니다.
	FString contextString;
	EnemyInfo = DT_EnemyInfo->FindRow<FEnemyInfo>(EnemyCode, contextString);

	if (EnemyInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter.cpp :: %d LINE :: EnemyInfo is null (EnemyCode = %s)"),
			__LINE__, *EnemyCode.ToString());
		return;
	}

	
	// 스켈레탈 메시 설정
	USkeletalMesh* skeletalMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo->SkeletalMeshPath));
	/// - LoadSynchronous(target) : target 에 해당하는 애셋을 동기 방식으로 로드하여 UObject* 형식으로 반환합니다.

	GetMesh()->SetSkeletalMesh(skeletalMesh);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// 최대 이동 속력 설정
	GetCharacterMovement()->MaxWalkSpeed = EnemyInfo->MaxMoveSpeed;

	// 캡슐 크기 설정
	GetCapsuleComponent()->SetCapsuleHalfHeight(EnemyInfo->CapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleRadius(EnemyInfo->CapsuleRadius);

	// BehaviorTree 설정
	BehaviorTree = Cast<UBehaviorTree>(
		GetManager(FStreamableManager)->LoadSynchronous(EnemyInfo->UseBehaviorTreeAssetPath));

	// 애님 인스턴스 클래스 설정
	GetMesh()->SetAnimInstanceClass(EnemyInfo->AnimClass);

	// Behavior Tree Run!
	if (IsValid(BehaviorTree))
	{
		Cast<AEnemyController>(GetController())->RunBehaviorTree(BehaviorTree);
	}
}
