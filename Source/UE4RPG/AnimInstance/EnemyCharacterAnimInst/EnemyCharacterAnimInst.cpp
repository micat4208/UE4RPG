#include "EnemyCharacterAnimInst.h"

void UEnemyCharacterAnimInst::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	APawn* owner = TryGetPawnOwner();

	if (!IsValid(owner)) return;

	VelocityLength = owner->GetVelocity().Size();
	
}
