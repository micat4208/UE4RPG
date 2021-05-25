#pragma once

#include "UE4RPG.h"
#include "Actor/Character/BaseCharacter.h"
#include "Struct/NpcInfo/NpcInfo.h"
#include "BaseNpc.generated.h"

UCLASS()
class UE4RPG_API ABaseNpc : 
	public ABaseCharacter
{
	GENERATED_BODY()

private :
	TSubclassOf<class UNpcDialogWidget> BP_NpcDialog;
	class UDataTable* DT_NpcInfo;

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Npc Code")
	FName NpcCode;

	FNpcInfo * NpcInfo;

protected :
	UPROPERTY(VisibleAnywhere)
	class UInteractableAreaComponent* InteractableArea;

public :
	ABaseNpc();

protected :
	virtual void BeginPlay() override;

private :
	void InitializeNpc();

public :
	FORCEINLINE FNpcInfo* GetNpcInfo() const
	{ return NpcInfo; }
	
};
