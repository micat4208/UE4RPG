#include "InventoryItemSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/Image.h"

UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjIniter) :
	Super(ObjIniter)
{
	// 이 슬롯에서 드래깅 작업을 허용합니다.
	bAllowDragOperation = true;
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// 드래그 시작 시 실행할 내용을 정의합니다.
	OnSlotDragStarted.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{

			// 슬롯이 비어있다면 실행 취소
			if (GetItemInfo()->IsEmpty()) return;

			TTuple<UUserWidget *, UImage*> dragWidget = CreateSlotDragWidget();
			UUserWidget* dragWidgetVisual = dragWidget.Get<0>();
			UImage* dragWidgetImage = dragWidget.Get<1>();

			// 드래그 시 표시되는 위젯을 설정합니다.
			dragDropOp->DefaultDragVisual = dragWidgetVisual;

			// 드래그 시 표시되는 이미지를 설정합니다.
			dragWidgetImage->SetBrushFromTexture(
				Cast<UTexture2D>(GetSlotImage()->Brush.GetResourceObject()));
			dragWidgetImage->SetBrushSize(FVector2D(60.0f, 60.0f));
		});

	OnSlotDragFinished.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{
			// Inventory Slot to Inventory Slot
			/// - Ori : Inventory Slot
			/// - Target(this) : Inventory Slot
			if (dragDropOp->OriginatedDragSlot->GetSlotType() == ESlotType::InventorySlot)
			{
				UInventoryItemSlot* originatedDragSlot = Cast<UInventoryItemSlot>(dragDropOp->OriginatedDragSlot);

				// 드래그 된 슬롯이 비어있다면 실행 X
				if (originatedDragSlot->GetItemInfo()->IsEmpty()) return;

				FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

				bool bIsSameItem =
					playerInfo->InventoryItemInfos[originatedDragSlot->GetItemSlotIndex()].ItemCode ==
					playerInfo->InventoryItemInfos[GetItemSlotIndex()].ItemCode;

				// 드래그를 시작시킨 슬롯과 드랍을 시킨 위치의 슬롯에 담긴 아이템이 동일한 아이템이라면 아이템 합침
				if (bIsSameItem)
					GetManager(UPlayerManager)->GetPlayerInventory()->MergeItem(originatedDragSlot, this);
				// 다른 아이템이라면 스왑
				else GetManager(UPlayerManager)->GetPlayerInventory()->SwapItem(originatedDragSlot, this);
			}


		});

	OnMouseRightButtonClickedEvent.AddLambda(
		[this]() 
		{
			if (GetItemInfo()->IsEmpty()) return;
			if (GetItemInfo()->ItemType == EItemType::Consumption);
		
		});
}

void UInventoryItemSlot::InitializeSlot(ESlotType slotType, FName itemCode, int32 itemSlotIndex)
{
	Super::InitializeSlot(slotType, itemCode);

	ItemSlotIndex = itemSlotIndex;

	UpdateItemCountText();
}

void UInventoryItemSlot::UpdateInventoryItemSlot()
{
	SetItemInfo(GetManager(UPlayerManager)->GetPlayerInfo()->InventoryItemInfos[ItemSlotIndex].ItemCode);
	UpdateItemImage();
	UpdateItemCountText();
}

void UInventoryItemSlot::UpdateItemCountText()
{
	auto& itemSlotInfo = GetManager(UPlayerManager)->GetPlayerInfo()->
		InventoryItemInfos[ItemSlotIndex];

	SetSlotItemCount(itemSlotInfo.ItemCount);
}
