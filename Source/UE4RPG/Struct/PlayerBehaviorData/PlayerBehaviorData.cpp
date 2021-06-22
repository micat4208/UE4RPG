#include "PlayerBehaviorData.h"

FPlayerBehaviorData::FPlayerBehaviorData(EPlayerBehavior::Type behavior)
{
	Behavior = behavior;
	Code = FName();
	Count = 0;
}

FPlayerBehaviorData::FPlayerBehaviorData(EPlayerBehavior::Type behavior, FName code, int32 count, int32 index)
{
	Behavior = behavior;
	Code = code;
	Count = count;
	IntegerData1 = index;
}
