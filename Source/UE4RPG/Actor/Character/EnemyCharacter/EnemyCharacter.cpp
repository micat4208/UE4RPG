#include "EnemyCharacter.h"

#include "Single/GameInstance/RPGGameInstance.h"

#include "Engine/DataTable.h"


AEnemyCharacter::AEnemyCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMY_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_EnemyInfo.DT_EnemyInfo'"));
	if (DT_ENEMY_INFO.Succeeded()) DT_EnemyInfo = DT_ENEMY_INFO.Object;

	EnemyCode = FName(TEXT("1000"));

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeEnemyCharacter();

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

}
