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

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkillControllerComponent * SkillController;

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
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* WeaponMesh;


public :
	APlayerCharacter();
	
public :
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public :
	// ��� ���� Mesh �� ���ϴ�.
	void ClearAllPartsMesh();

	// ������ ���� ����
	void LinkMasterPose();

private :
	// �⺻ ���� �޼���
	void RegularAttack();

public :
	FORCEINLINE TMap<EPartsType, class USkeletalMeshComponent*>& GetParts()
	{ return Parts; }

	FORCEINLINE class UCharacterMovementHelperComponent* GetCharacterMovementHelper() const
	{ return CharacterMovementHelper; }

	FORCEINLINE class UPlayerInteractComponent* GetPlayerInteract() const
	{ return PlayerInteract; }

	FORCEINLINE class USkillControllerComponent* GetSkillController() const
	{ return SkillController; }

};
