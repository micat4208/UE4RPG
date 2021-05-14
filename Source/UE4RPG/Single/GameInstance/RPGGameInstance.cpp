#include "RPGGameInstance.h"

#include "Single/PlayerManager/PlayerManager.h"

void URPGGameInstance::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassInstance = NewObject<UManagerClass>(this, managerClass,
		NAME_None, EObjectFlags::RF_MarkAsRootSet);

	ManagerClasses.Add(managerClass->GetName(), managerClassInstance);

	managerClassInstance->InitManagerClass();
}

void URPGGameInstance::Init()
{
	Super::Init();

	RegisterManagerClass(UPlayerManager::StaticClass());
}

void URPGGameInstance::Shutdown()
{

	// 할당된 모든 ManagerClass 들을 해제합니다.
	for (auto managerClassData : ManagerClasses)
	{
		// nullptr 확인
		if (!managerClassData.Value) continue;

		// 해당 객체가 GC 에 의해 해제된 객체인지 확인합니다.
		if (!managerClassData.Value->IsValidLowLevel()) continue;

		managerClassData.Value->ShutdownManagerClass();

		// 객체 소멸
		managerClassData.Value->ConditionalBeginDestroy();
	}
	ManagerClasses.Empty();

	Super::Shutdown();
}
