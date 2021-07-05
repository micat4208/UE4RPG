#pragma once

#include "UE4RPG.h"
#include "Components/ActorComponent.h"

#include "Struct/SkillInfo/SkillInfo.h"

#include "SkillControllerComponent.generated.h"

#ifndef MAX_SKILL_QUEUE_SIZE
#define MAX_SKILL_QUEUE_SIZE	2
#endif

UCLASS()
class UE4RPG_API USkillControllerComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	class UDataTable* DT_SkillInfo;

private :
	class APlayerCharacter* PlayerCharacter;

	// �������� ��ų ������ ��Ÿ���ϴ�.
	FSkillInfo* CurrentSkillInfo;

	// �����ų ��ų���� ��Ƶ� ť
	TQueue<FSkillInfo*> SkillQueue;

	// ���� �ǻ����Ѿ� �ϴ� ��ų ������ ��Ÿ���ϴ�.
	int32 SkillCount;

	// ��ų�� ��û�� �� ������ ��Ÿ���ϴ�.
	/// - �� ���� false ��� ��ų�� ��û�� �� �����ϴ�.
	bool bIsRequestable;

public:	
	USkillControllerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// ��ų ������ ��û�մϴ�.
	void RequestSkill(FName skillCode);

	// ��ų�� �������� �˸��ϴ�.
	void SkillFinished();

	// ��ų ������ �����մϴ�.
	void CreateSkillRange();

private :
	// ��ų�� ������� ó���մϴ�.
	void SkillProcedure();

	// ��ų�� �����մϴ�.
	void CastSkill(FSkillInfo* skillInfo);
		
};
