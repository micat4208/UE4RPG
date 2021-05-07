#pragma once

#include "UE4RPG.h"
#include "Actor/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE4RPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* SpringArm;

public :
	APlayerCharacter();
	
public :
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
