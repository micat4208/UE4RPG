#include "InventoryItemSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/Image.h"

UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjIniter) :
	Super(ObjIniter)
{
	// �� ���Կ��� �巡�� �۾��� ����մϴ�.
	bAllowDragOperation = true;
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	// �巡�� ���� �� ������ ������ �����մϴ�.
	OnSlotDragStarted.AddLambda(
		[this](USlotDragDropOperation* dragDropOp)
		{

			// ������ ����ִٸ� ���� ���
			if (GetItemInfo()->IsEmpty()) return;

			TTuple<UUserWidget *, UImage*> dragWidget = CreateSlotDragWidget();
			UUserWidget* dragWidgetVisual = dragWidget.Get<0>();
			UImage* dragWidgetImage = dragWidget.Get<1>();

			// �巡�� �� ǥ�õǴ� ������ �����մϴ�.
			dragDropOp->DefaultDragVisual = dragWidgetVisual;

			// �巡�� �� ǥ�õǴ� �̹����� �����մϴ�.
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

				// �巡�� �� ������ ����ִٸ� ���� X
				if (originatedDragSlot->GetItemInfo()->IsEmpty()) return;

				FPlayerCharacterInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

				bool bIsSameItem =
					playerInfo->InventoryItemInfos[originatedDragSlot->GetItemSlotIndex()].ItemCode ==
					playerInfo->InventoryItemInfos[GetItemSlotIndex()].ItemCode;

				// �巡�׸� ���۽�Ų ���԰� ����� ��Ų ��ġ�� ���Կ� ��� �������� ������ �������̶�� ������ ��ħ
				if (bIsSameItem)
					GetManager(UPlayerManager)->GetPlayerInventory()->MergeItem(originatedDragSlot, this);
				// �ٸ� �������̶�� ����
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
