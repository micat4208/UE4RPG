#include "PlayerCharacter.h"

#include "AnimInstance/PlayerCharacterAnimInst/PlayerCharacterAnimInst.h"

#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Component/CharacterMovementHelper/CharacterMovementHelperComponent.h"
#include "Component/PlayerInteract/PlayerInteractComponent.h"

APlayerCharacter::APlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_FEMALE_BASE(
		TEXT("SkeletalMesh'/Game/Resources/Character/GhostLady_S1/Meshes/Characters/Combines/SK_FemaleBase.SK_FemaleBase'"));
	if (SK_FEMALE_BASE.Succeeded()) GetMesh()->SetSkeletalMesh(SK_FEMALE_BASE.Object);

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInst> BP_PLAYER_CHARACTER(
		TEXT("AnimBlueprint'/Game/Blueprints/AnimInstance/PlayerCharacter/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (BP_PLAYER_CHARACTER.Succeeded()) BP_PlayerCharacter = BP_PLAYER_CHARACTER.Class;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA_COMPONENT"));
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM_COMPONENT"));
	CharacterMovementHelper = CreateDefaultSubobject<UCharacterMovementHelperComponent>(TEXT("CHARACTER_MOVEMENT_HELPER"));
	PlayerInteract = CreateDefaultSubobject<UPlayerInteractComponent>(TEXT("PLAYER_INTERACT_COMPONENT"));

	HeadMesh		= GetMesh();
	HairMesh		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_HAIR"));
	TopMesh			= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_TOP"));
	BottomMesh		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_BOTTOM"));
	RightGloveMesh	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_RGLOVE"));
	LeftGloveMesh	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_LGLOVE"));
	ShoesMesh		= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_SHOES"));

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

	GetMesh()->SetAnimInstanceClass(BP_PlayerCharacter);

	// Pawn 의 회전이 컨트롤러의 Yaw 회전을 따르지 않도록 합니다.
	bUseControllerRotationYaw = false;

	// 이동하는 방향으로 캐릭터가 회전하도록 합니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	/// - 이 속성을 사용할 경우 bUseControllerRotationYaw 속성이 false 로 설정되었는지 확인해야 합니다.

	// 회전 속도를 설정합니다.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	HairMesh->SetupAttachment(HeadMesh);
	TopMesh->SetupAttachment(HeadMesh);
	BottomMesh->SetupAttachment(HeadMesh);
	RightGloveMesh->SetupAttachment(HeadMesh);
	LeftGloveMesh->SetupAttachment(HeadMesh);
	ShoesMesh->SetupAttachment(HeadMesh);

	Parts.Empty();
	Parts.Add(EPartsType::PT_Hair, HairMesh);
	Parts.Add(EPartsType::PT_Head, HeadMesh);
	Parts.Add(EPartsType::PT_Top, TopMesh);
	Parts.Add(EPartsType::PT_Bottom, BottomMesh);
	Parts.Add(EPartsType::PT_RightGlove, RightGloveMesh);
	Parts.Add(EPartsType::PT_LeftGlove, LeftGloveMesh);
	Parts.Add(EPartsType::PT_Shoes, ShoesMesh);


}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,
		CharacterMovementHelper, &UCharacterMovementHelperComponent::RunKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released,
		CharacterMovementHelper, &UCharacterMovementHelperComponent::RunKeyReleased);

	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed,
		PlayerInteract, &UPlayerInteractComponent::TryInteraction);

	PlayerInputComponent->BindAxis(TEXT("MouseWheel"), SpringArm, &UZoomableSpringArmComponent::ZoomCamera);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), 
		CharacterMovementHelper, &UCharacterMovementHelperComponent::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"),
		CharacterMovementHelper, &UCharacterMovementHelperComponent::InputVertical);

}

void APlayerCharacter::ClearAllPartsMesh()
{
	for (auto partsMeshComponent : Parts)
	{
		if (IsValid(partsMeshComponent.Value))
			partsMeshComponent.Value->SetSkeletalMesh(nullptr);
	}
}

void APlayerCharacter::LinkMasterPose()
{
	HairMesh->AttachToComponent(HeadMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Socket_Hair")));

	TopMesh->SetMasterPoseComponent(HeadMesh);
	BottomMesh->SetMasterPoseComponent(HeadMesh);
	LeftGloveMesh->SetMasterPoseComponent(HeadMesh);
	RightGloveMesh->SetMasterPoseComponent(HeadMesh);
	ShoesMesh->SetMasterPoseComponent(HeadMesh);
}
