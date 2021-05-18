#include "BaseNpc.h"

#include "Component/InteractableArea/InteractableAreaComponent.h"

ABaseNpc::ABaseNpc()
{
	InteractableArea = CreateDefaultSubobject<UInteractableAreaComponent>(TEXT("INTERACTABLE_AREA_COMPONENT"));

	InteractableArea->SetupAttachment(GetRootComponent());
	InteractableArea->SetSphereRadius(250.0f);
}
