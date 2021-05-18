#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractComponent.generated.h"


UCLASS()
class UE4RPG_API UPlayerInteractComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	TArray<class UInteractableAreaComponent*> InteractableComponents;

public:	
	UPlayerInteractComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// 상호작용 가능한 객체로 추가합니다.
	/// - newInteractable : 상호작용 가능한 객체를 전달합니다.
	void AddInteractable(class UInteractableAreaComponent* newInteractable);

	// 상호작용 가능한 객체에서 제외시킵니다.
	/// - removeInteractable : 상호작용 가능했던 객체를 전달합니다.
	void RemoveInteractable(class UInteractableAreaComponent* removeInteractable);
		
};
