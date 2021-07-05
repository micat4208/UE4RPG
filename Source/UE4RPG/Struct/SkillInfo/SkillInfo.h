#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillInfo.generated.h"


USTRUCT(BlueprintType)
struct UE4RPG_API FSkillInfo : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// 스킬 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillCode;

	// 스킬 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillName;

	// 무기와 함께 사용 가능한 스킬임을 나타냅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeUsedWithWeapon;


	// AnimMontage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* AnimMontage;


};
