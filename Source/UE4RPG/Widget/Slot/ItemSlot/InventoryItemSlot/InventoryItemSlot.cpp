#include "InventoryItemSlot.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"
#include "Widget/ClosableWnd/PlayerEquipmentWnd/PlayerEquipmentWnd.h"
#include "Widget/Slot/ItemSlot/PlayerEquipSlot/PlayerEquipSlot.h"

#include "Component/PlayerBehaviorBroadcast/PlayerBehaviorBroadcastComponent.h"
#include "Components/Image.h"

UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjIniter) :
	Super(ObjIniter)
{
	// 이 슬롯에서 드래깅 작업을 허용합니다.
	bAllowDragOperation = true;

	InventoryWnd = nullptr;
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
			if (InventoryWnd->bIsTradeMode) return;
			if (GetItemInfo()->IsEmpty()) return;
			if (GetItemInfo()->ItemType == EItemType::Consumption)
				GetManager(UPlayerManager)->GetPlayerController()->GetPlayerBehaviorBroadcast()->UseInventoryItem(
					GetItemSlotIndex());
		});

	// 우클릭 시 장비 아이템을 장착 시킵니다.
	OnMouseRightButtonClickedEvent.AddUObject(this, &UInventoryItemSlot::AttachToEquipItemSlot);
	/// - AddUObject  : 이벤트나, 멀티캐스트 델리게이트에 UObject 멤버 함수를 바인딩시킵니다.
	/// - BindUObject : 싱글캐스트 델리게이트에 UObject 멤버 함수를 바인딩시킵니다.
	/// - AddDyanmic  : 이벤트나, 다이나믹 멀티캐스트 델리게이트에 UObject 멤버 함수를 바인딩시킵니다.
	/// - AddLambda	  : 이벤트나, 멀티캐스트 델리게이트에 람다문을 바인딩시킵니다.
	/// - BindLambda  : 싱글캐스트 델리게이트에 람다문을 바인딩시킵니다.
	/// 
	/// - UObject (언리얼 오브젝트) : 언리얼 엔진의 관리를 받는 객체를 나타냅니다.
	///   부모 클래스가 UObject 로 되어있음.
	///   UCLASS() 를 작성.
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

void UInventoryItemSlot::AttachToEquipItemSlot()
{
	// 상점을 이용중이라면 장착되지 않도록 합니다.
	if (InventoryWnd->bIsTradeMode) return;


	// 아이템 정보
	FItemInfo* itemInfo = GetItemInfo();

	// 만약 해당 슬롯에 아이템이 존재하지 않는다면 실행 X
	if (itemInfo->IsEmpty()) return;

	// 만약 해당 아이템이 장비 아이템이 아니라면 실행 X
	if (itemInfo->ItemType != EItemType::Equipment) return;


	// PlayerInventory 객체를 얻습니다.
	UPlayerInventory* playerInventory = GetManager(UPlayerManager)->GetPlayerInventory();

	// 장비 창을 얻습니다.
	UPlayerEquipmentWnd* equipmentWnd = playerInventory->GetPlayerEquipmentWnd();

	// 아이템 장착
	playerInventory->EquipItem(itemInfo->ItemCode);

	// 해당 슬롯을 비웁니다.
	playerInventory->RemoveItem(ItemSlotIndex);

	// 장비창을 갱신합니다.
	equipmentWnd->UpdatePartsSlots();
}
