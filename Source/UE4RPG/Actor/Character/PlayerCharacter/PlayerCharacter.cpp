#include "PlayerCharacter.h"
#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_FEMALE_BASE(
		TEXT("SkeletalMesh'/Game/GhostLady_S1/Meshes/Characters/Combines/SK_FemaleBase.SK_FemaleBase'"));
	if (SK_FEMALE_BASE.Succeeded()) GetMesh()->SetSkeletalMesh(SK_FEMALE_BASE.Object);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA_COMPONENT"));
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM_COMPONENT"));

	
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	// SpringArm 의 회전이 Controller 의 (Yaw, Pitch) 회전을 사용하도록 합니다.
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = false;
	SpringArm->TargetOffset = FVector::UpVector * 88.0f;


	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0));

	// Pawn 의 회전이 컨트롤러의 Yaw 회전을 따르지 않도록 합니다.
	bUseControllerRotationYaw = false;

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MouseWheel"), SpringArm, &UZoomableSpringArmComponent::ZoomCamera);

}
