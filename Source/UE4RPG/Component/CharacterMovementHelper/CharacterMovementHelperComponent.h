#pragma once

#include "UE4RPG.h"
#include "Components/ActorComponent.h"
#include "CharacterMovementHelperComponent.generated.h"

UCLASS()
class UE4RPG_API UCharacterMovementHelperComponent final : 
	public UActorComponent
{
	GENERATED_BODY()

private :
	class APlayerCharacter* PlayerCharacter;
	class UCharacterMovementComponent* MovementComponent;

	float WalkSpeed;
	float RunSpeed;




public:	
	UCharacterMovementHelperComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public :
	void InputHorizontal(float axis);
	void InputVertical(float axis);
		
	void RunKeyPressed();
	void RunKeyReleased();

};
