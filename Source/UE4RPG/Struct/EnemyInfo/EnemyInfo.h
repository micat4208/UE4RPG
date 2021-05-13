#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Animation/AnimInstance.h"
#include "EnemyInfo.generated.h"

USTRUCT(BlueprintType)
struct UE4RPG_API FEnemyInfo :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FName EnemyCode;

	// 적 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FText EnemyName;
	
	// 캡슐 절반 높이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	float CapsuleHalfHeight;

	// 캡슐 반지름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	float CapsuleRadius;

	// 적 Skeletal Mesh 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FSoftObjectPath SkeletalMeshPath;

	// 적 애님 블루프린트 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	TSubclassOf<UAnimInstance> AnimClass;
	
	// 적 최대 이동 속력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	float MaxMoveSpeed;
	
	// Behavior Tree 애셋 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본")
	FSoftObjectPath UseBehaviorTreeAssetPath;
	
public :
	FEnemyInfo();

};
