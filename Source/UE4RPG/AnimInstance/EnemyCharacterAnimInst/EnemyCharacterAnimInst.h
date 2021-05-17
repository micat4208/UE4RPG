#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacterAnimInst.generated.h"

UCLASS()
class UE4RPG_API UEnemyCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

public :
	virtual void NativeUpdateAnimation(float dt) override;

};
