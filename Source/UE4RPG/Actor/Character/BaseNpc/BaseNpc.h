#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "BaseNpc.generated.h"

UCLASS()
class UE4RPG_API ABaseNpc : 
	public ABaseCharacter
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere)
	class UInteractableAreaComponent* InteractableArea;

public :
	ABaseNpc();
	
};
