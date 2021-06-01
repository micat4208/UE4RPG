#include "ItemSlot.h"

UItemSlot::UItemSlot(const FObjectInitializer& objInitializer) : 
	Super(objInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;
}

void UItemSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	Super::InitializeSlot(slotType, inCode);

	SetItemInfo(inCode);
	
	LOG(TEXT("%s.cpp :: LINE %d :: ItemName = %s"),
		__CLSNAME__, __LINE__, *ItemInfo.ItemName.ToString());
}

void UItemSlot::SetItemInfo(FName itemCode)
{
	// ������ ���� ����
	FString contextString;
	FItemInfo* findedItemInfo = nullptr;

	// ������ �ڵ尡 ����ִٸ�
	if (itemCode.IsNone())
	{
		// ������ ������ ���ϴ�.
		ItemInfo = FItemInfo();
		return;
	}

	// ������ �ڵ尡 ������� �ʴٸ� ������ �ڵ带 �̿��Ͽ� ������ ������ ����ϴ�.
	else findedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	if (findedItemInfo == nullptr) ItemInfo = FItemInfo();
	else ItemInfo = *findedItemInfo;
}
