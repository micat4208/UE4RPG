#pragma once

#include "UE4RPG.h"
#include "Actor/Character/BaseCharacter.h"

#include "Struct/EnemyInfo/EnemyInfo.h"

#include "EnemyCharacter.generated.h"

UCLASS()
class UE4RPG_API AEnemyCharacter : 
	public ABaseCharacter
{
	GENERATED_BODY()

private:
	class UDataTable* DT_EnemyInfo;

public :
	// 적 캐릭터 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Code")
	FName EnemyCode;

	// 적 캐릭터 정보를 나타냅니다.
	FEnemyInfo* EnemyInfo;

public :
	AEnemyCharacter();

protected :
	virtual void BeginPlay() override;

public :
	// 적 캐릭터를 초기화합니다.
	void InitializeEnemyCharacter();

};
