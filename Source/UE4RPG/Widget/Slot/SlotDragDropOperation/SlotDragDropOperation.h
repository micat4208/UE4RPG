#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDropOperation.generated.h"

// 슬롯 드래그 드랍 작업 객체를 나타내기 위한 클래스입니다.
UCLASS()
class UE4RPG_API USlotDragDropOperation final : 
public UDragDropOperation
{
	GENERATED_BODY()

public :
	// 드래그가 시작된 슬롯을 나타냅니다.
	class UBaseSlot* OriginatedDragSlot;
	
};
