#pragma once

#include "UE4RPG.h"
#include "Actor/Character/BaseCharacter.h"
#include "BaseNpc.generated.h"

UCLASS()
class UE4RPG_API ABaseNpc : 
	public ABaseCharacter
{
	GENERATED_BODY()

private :
	TSubclassOf<class UNpcDialogWidget> BP_NpcDialog;

protected :
	UPROPERTY(VisibleAnywhere)
	class UInteractableAreaComponent* InteractableArea;

public :
	ABaseNpc();

protected :
	virtual void BeginPlay() override;
	
};
