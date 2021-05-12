#include "PlayerCharacter.h"
#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Component/CharacterMovementHelper/CharacterMovementHelperComponent.h"

APlayerCharacter::APlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_FEMALE_BASE(
		TEXT("SkeletalMesh'/Game/Resources/Character/GhostLady_S1/Meshes/Characters/Combines/SK_FemaleBase.SK_FemaleBase'"));
	if (SK_FEMALE_BASE.Succeeded()) GetMesh()->SetSkeletalMesh(SK_FEMALE_BASE.Object);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA_COMPONENT"));
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM_COMPONENT"));
	CharacterMovementHelper = CreateDefaultSubobject<UCharacterMovementHelperComponent>(TEXT("CHARACTER_MOVEMENT_HELPER"));
	
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

	// 이동하는 방향으로 캐릭터가 회전하도록 합니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	/// - 이 속성을 사용할 경우 bUseControllerRotationYaw 속성이 false 로 설정되었는지 확인해야 합니다.

	// 회전 속도를 설정합니다.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MouseWheel"), SpringArm, &UZoomableSpringArmComponent::ZoomCamera);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), 
		CharacterMovementHelper, &UCharacterMovementHelperComponent::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"),
		CharacterMovementHelper, &UCharacterMovementHelperComponent::InputVertical);

}
