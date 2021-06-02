#include "ItemSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"

#include "Components/Image.h"



UItemSlot::UItemSlot(const FObjectInitializer& objInitializer) : 
	Super(objInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DT_ItemInfo = DT_ITEM_INFO.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_NULL(
		TEXT("Texture2D'/Game/Resources/Image/Slot/T_Null.T_Null'"));
	if (T_NULL.Succeeded()) T_Null = T_NULL.Object;
}

void UItemSlot::InitializeSlot(ESlotType slotType, FName inCode)
{
	Super::InitializeSlot(slotType, inCode);

	SetItemInfo(inCode);
	
	UpdateItemImage();
}

void UItemSlot::UpdateItemImage()
{
	UTexture2D* itemImage = nullptr;


	// 아이템 정보가 비어있다면 투명한 이미지 사용
	if (ItemInfo.IsEmpty()) itemImage = T_Null;

	// 아이템 정보가 비어있지 않다면 아이템 이미지 로드
	else
	{
		// 아이템 이미지 경로가 비어있다면 투명한 이미지 사용
		if (ItemInfo.ItemImagePath.IsNull()) itemImage = T_Null;

		// 아이템 이미지 경로가 비어있지 않다면 아이템 이미지를 로드하여 사용
		else itemImage = Cast<UTexture2D>(
			GetManager(FStreamableManager)->LoadSynchronous(ItemInfo.ItemImagePath));
	}

	// 아이템 이미지 적용
	if (itemImage) GetSlotImage()->SetBrushFromTexture(itemImage);
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
