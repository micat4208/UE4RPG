#pragma once

#include "UE4RPG.h"
#include "Actor/Character/BaseCharacter.h"
#include "Enum/PartsType.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE4RPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private :
	TSubclassOf<class UPlayerCharacterAnimInst> BP_PlayerCharacter;


private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCharacterMovementHelperComponent * CharacterMovementHelper;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerInteractComponent * PlayerInteract;

protected :
	UPROPERTY()
	TMap<EPartsType, class USkeletalMeshComponent*> Parts;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* HeadMesh;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* HairMesh;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* TopMesh;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* BottomMesh;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* RightGloveMesh;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* LeftGloveMesh;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* ShoesMesh;


public :
	APlayerCharacter();
	
public :
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public :
	// 모든 파츠 Mesh 를 비웁니다.
	void ClearAllPartsMesh();

	// 마스터 포즈 연결
	void LinkMasterPose();

public :
	FORCEINLINE TMap<EPartsType, class USkeletalMeshComponent*>& GetParts()
	{ return Parts; }

	FORCEINLINE class UCharacterMovementHelperComponent* GetCharacterMovementHelper() const
	{ return CharacterMovementHelper; }

	FORCEINLINE class UPlayerInteractComponent* GetPlayerInteract() const
	{ return PlayerInteract; }


};
