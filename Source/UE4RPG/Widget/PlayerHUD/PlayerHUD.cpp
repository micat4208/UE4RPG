#include "PlayerHUD.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUD::NativeConstruct()
{
	Func(FillHpBar, (float current, float max), this)
	{ ProgressBar_Hp->SetPercent(current / max); };

	Super::NativeConstruct();

	FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();
	TMap<ECharacterStatusAttribute, float>& statusAttributes = playerInfo->StatusAttributes;

	// ���� ��ġ�� ǥ��
	FillHpBar(statusAttributes[ECharacterStatusAttribute::Hp], statusAttributes[ECharacterStatusAttribute::MaxHp]);

	// ��ġ ���� �� ����� ���� ����
	GetManager(UPlayerManager)->GetPlayerInfo()->OnStatusAttributesChanged.AddLambda(
		[this, playerInfo, statusAttributes, FillHpBar]
		(ECharacterStatusAttribute changedStatusAttribute, float prev, float current)
		{
			switch (changedStatusAttribute)
			{
			case ECharacterStatusAttribute::Hp:
				FillHpBar(current, statusAttributes[ECharacterStatusAttribute::MaxHp]);
				break;
			}
		});

}
