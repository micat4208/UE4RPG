#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableAreaComponent.generated.h"

DECLARE_EVENT_OneParam(UInteractableAreaComponent, FInteractEvent, UInteractableAreaComponent*)
// 이벤트
/// - 선언된 클래스 내부에서만 호출할 수 잇는 Multicast_Delegate 입니다.


UCLASS()
class UE4RPG_API UInteractableAreaComponent final : 
	public USphereComponent
{
	GENERATED_BODY()

public :


	// 상호작용이 시작될 때 발생하는 이벤트
	FInteractEvent OnInteractStarted;

public :
	virtual void BeginPlay() override;

public :
	void StartInteract();

private :
	UFUNCTION()
	void OnPlayerCharacterDetected(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerCharacterLost(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

		
	
};
