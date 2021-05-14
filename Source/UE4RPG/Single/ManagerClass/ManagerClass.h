#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerClass.generated.h"

#ifndef MANAGER_INSTANCE
#define MANAGER_INSTANCE
#define GetManager(ManagerClassType) (Cast<URPGGameInstance>(GetWorld()->GetGameInstance())->GetManagerClass<ManagerClassType>())
#endif

UCLASS(Abstract)
class UE4RPG_API UManagerClass : public UObject
{
	GENERATED_BODY()

public :
	// 해당 객체가 생성될 때 호출되는 메서드
	FORCEINLINE virtual void InitManagerClass() {}

	// 해당 객체가 소멸될 때 호출되는 메서드
	FORCEINLINE virtual void ShutdownManagerClass() {}
	
};
