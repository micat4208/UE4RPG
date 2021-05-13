#include "CharacterMovementHelperComponent.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

UCharacterMovementHelperComponent::UCharacterMovementHelperComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCharacterMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	MovementComponent = PlayerCharacter->GetCharacterMovement();

	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;
	RunKeyReleased();
}

void UCharacterMovementHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterMovementHelperComponent::InputHorizontal(float axis)
{
	FVector controllerRightVector = Cast<AActor>(PlayerCharacter->GetController())->
		GetActorRightVector();

	PlayerCharacter->AddMovementInput(
		controllerRightVector, axis);
}

void UCharacterMovementHelperComponent::InputVertical(float axis)
{
	// 컨트롤러 회전중 Yaw 회전을 얻습니다.
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Type::X);
	/// - FRotationMatrix : 회전된 좌표계 정보를 저장하는 행렬을 나타냅니다.
	/// - 생성자 인수에 어떠한 회전값을 전달하게 된다면, 캐릭터의 중심이 (0, 0, 0) 인 상태에서
	///   각 축에 따라 얼마나 회전되어 있는지를 나타내게 됩니다.
	/// - GetUnitAxis(EAxis) : EAxis 축으로의 방향을 반환합니다.

	PlayerCharacter->AddMovementInput(forwardVector, axis);
}

void UCharacterMovementHelperComponent::RunKeyPressed()
{
	MovementComponent->MaxWalkSpeed = RunSpeed;
}

void UCharacterMovementHelperComponent::RunKeyReleased()
{
	MovementComponent->MaxWalkSpeed = WalkSpeed;
}