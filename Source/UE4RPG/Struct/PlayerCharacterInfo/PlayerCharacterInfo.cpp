#include "PlayerCharacterInfo.h"


FPlayerCharacterInfo::FPlayerCharacterInfo()
{
	InventorySlotCount = 30;

	// Test Code ...
	Silver = 100000;

	for (int32 i = 0; i < InventorySlotCount; ++i)
		InventoryItemInfos.Add(FItemSlotInfo());

	InventoryItemInfos[0] = (FItemSlotInfo(FName(TEXT("90009")), 3, 100));

	StatusAttributes.Add(ECharacterStatusAttribute::MaxHp, 1000.0f);
	StatusAttributes.Add(ECharacterStatusAttribute::Hp, 900.0f);

	// �⺻ ��� ����
	DefaultPartsInfos.Empty();
	DefaultPartsInfos.Add(EPartsType::PT_Hair,		FItemSlotInfo(FName("101000")));
	DefaultPartsInfos.Add(EPartsType::PT_Head,		FItemSlotInfo(FName("111000")));
	DefaultPartsInfos.Add(EPartsType::PT_Top,		FItemSlotInfo(FName("21000")));
	DefaultPartsInfos.Add(EPartsType::PT_Bottom,	FItemSlotInfo(FName("11000")));
	DefaultPartsInfos.Add(EPartsType::PT_Glove,		FItemSlotInfo(FName("31000")));
	DefaultPartsInfos.Add(EPartsType::PT_Shoes,		FItemSlotInfo(FName("41000")));
	DefaultPartsInfos.Add(EPartsType::PT_Weapon,	FItemSlotInfo());

	PartsInfos.Empty();
	PartsInfos.Add(EPartsType::PT_Hair,		FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Head,		FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Top,		FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Bottom,	FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Glove,	FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Shoes,	FItemSlotInfo());
	PartsInfos.Add(EPartsType::PT_Weapon,	FItemSlotInfo());
}

void FPlayerCharacterInfo::SetStatusAttributes(ECharacterStatusAttribute statusAttributes, float value)
{
	if (StatusAttributes.Contains(statusAttributes))
	{
		// ���� �� ��ġ�� �����մϴ�.
		float prevValue = StatusAttributes[statusAttributes];

		// ��ġ�� �����ŵ�ϴ�.
		StatusAttributes[statusAttributes] = value;

		// ��ġ ���� �븮�� ȣ��
		if (OnStatusAttributesChanged.IsBound())
			OnStatusAttributesChanged.Broadcast(statusAttributes, prevValue, value);
		/// - ù ��° : �����Ų ���� �Ӽ�
		/// - �� ��° : ���� �� ���� �Ӽ� ��ġ
		/// - �� ��° : ���� �� ���� �Ӽ� ��ġ
	}

}

void FPlayerCharacterInfo::AddStatusAttributes(ECharacterStatusAttribute statusAttributes, float value)
{
	if (StatusAttributes.Contains(statusAttributes))
	{
		// ���� �� ��ġ�� �����մϴ�.
		float prevValue = StatusAttributes[statusAttributes];

		// ��ġ�� �����ŵ�ϴ�.
		float currentValue = StatusAttributes[statusAttributes] += value;

		if (OnStatusAttributesChanged.IsBound())
			OnStatusAttributesChanged.Broadcast(statusAttributes, prevValue, currentValue);
	}
}
