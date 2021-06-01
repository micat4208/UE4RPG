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
	// 아이템 정보 설정
	FString contextString;
	FItemInfo* findedItemInfo = nullptr;

	// 아이템 코드가 비어있다면
	if (itemCode.IsNone())
	{
		// 아이템 정보를 비웁니다.
		ItemInfo = FItemInfo();
		return;
	}

	// 아이템 코드가 비어있지 않다면 아이템 코드를 이용하여 아이템 정보를 얻습니다.
	else findedItemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	if (findedItemInfo == nullptr) ItemInfo = FItemInfo();
	else ItemInfo = *findedItemInfo;
}
