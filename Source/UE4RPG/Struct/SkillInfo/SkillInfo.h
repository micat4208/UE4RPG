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
	// ��ų �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillCode;

	// ��ų �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillName;

	// ����� �Բ� ��� ������ ��ų���� ��Ÿ���ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeUsedWithWeapon;


	// AnimMontage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* AnimMontage;


};
