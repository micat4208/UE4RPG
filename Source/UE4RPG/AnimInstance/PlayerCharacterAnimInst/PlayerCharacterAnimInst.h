#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInst.generated.h"

UCLASS()
class UE4RPG_API UPlayerCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()

protected :
	// 애님 인스턴스 클래스를 소유하는 Pawn 객체를 나타냅니다.
	class APlayerCharacter* Owner;

	// 현재 캐릭터 속력을 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

public :
	virtual void NativeUpdateAnimation(float dt) override;

	UFUNCTION()
	void AnimNotify_SkillFinish();

	
};
