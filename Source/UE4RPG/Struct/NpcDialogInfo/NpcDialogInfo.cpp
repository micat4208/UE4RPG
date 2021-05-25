#include "NpcDialogInfo.h"

bool FNpcDialogInfo::IsEmpty() const
{
	return (DialogText.Num() == 0);
}
