#include "PlayerCharacterAnimInst.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Component/SkillController/SkillControllerComponent.h"

void UPlayerCharacterAnimInst::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	Owner = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner)) return;

	VelocityLength = Owner->GetVelocity().Size();
}

void UPlayerCharacterAnimInst::AnimNotify_SkillFinish()
{
	if (!IsValid(Owner)) return;

	Owner->GetSkillController()->SkillFinished();
}

void UPlayerCharacterAnimInst::AnimNotify_ActiveSkillRange()
{
	if (!IsValid(Owner)) return;
	Owner->GetSkillController()->CreateSkillRange();
}
