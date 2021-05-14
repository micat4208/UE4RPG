#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Single/ManagerClass/ManagerClass.h"

#include "RPGGameInstance.generated.h"

#ifndef GAME_INST
#define GAME_INST
#define GetGameInst(worldContextObject) (Cast<URPGGameInstance>(worldContextObject->GetGameInstance()))
#endif

UCLASS()
class UE4RPG_API URPGGameInstance final : 
	public UGameInstance
{
	GENERATED_BODY()

private :
	// 등록한 매니저 클래스 객체들을 저장합니다.
	TMap<FString, UManagerClass*> ManagerClasses;

private :
	// Manager Class 를 등록합니다.
	/// - 등록한 Manager Class 는 인스턴스화 되어 ManagerClasses Map 에 추가됩니다.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public :
	// 등록한 ManagerClass 를 얻습니다.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{ return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]); }

	// 애셋 로딩을 위한 StreamableManager 를 얻는 메서드
	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{ return &UAssetManager::GetStreamableManager(); }


public :
	// GameInstance 가 초기화될 때 호출되는 메서드
	virtual void Init() override;

	// GameInstance 가 소멸될 때 호출되는 메서드
	virtual void Shutdown() override;

};
