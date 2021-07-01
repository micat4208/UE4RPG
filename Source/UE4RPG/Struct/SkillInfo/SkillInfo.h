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

	// AnimMontage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* AnimMontage;
};
