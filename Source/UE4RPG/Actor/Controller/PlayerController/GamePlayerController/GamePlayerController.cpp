#include "GamePlayerController.h"

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// MouseX, Y �Է� �� ȣ���� �޼��带 ���ε���ŵ�ϴ�.
	InputComponent->BindAxis(TEXT("MouseX"), this, &AGamePlayerController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &AGamePlayerController::MouseYInput);
}

void AGamePlayerController::MouseXInput(float axis)
{
	// ��Ʈ�ѷ��� Yaw ȸ������ axis �� ���մϴ�.
	/// - axis : ���콺�� �������� �̵���Ų�ٸ� -1
	/// -        ���콺�� ���������� �̵���Ų�ٸ� 1
	AddYawInput(axis);
}

void AGamePlayerController::MouseYInput(float axis)
{
	// ��Ʈ�ѷ��� Pitch ȸ������ axis �� ���մϴ�.
	/// - axis : ���콺�� �������� �̵���Ų�ٸ� -1
	/// -        ���콺�� �Ʒ������� �̵���Ų�ٸ� 1
	AddPitchInput(axis);
}
