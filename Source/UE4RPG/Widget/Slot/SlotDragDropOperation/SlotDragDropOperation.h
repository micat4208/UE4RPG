#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDropOperation.generated.h"

// ���� �巡�� ��� �۾� ��ü�� ��Ÿ���� ���� Ŭ�����Դϴ�.
UCLASS()
class UE4RPG_API USlotDragDropOperation final : 
public UDragDropOperation
{
	GENERATED_BODY()

public :
	// �巡�װ� ���۵� ������ ��Ÿ���ϴ�.
	class UBaseSlot* OriginatedDragSlot;
	
};
