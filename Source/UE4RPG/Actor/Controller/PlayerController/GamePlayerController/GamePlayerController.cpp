#include "GamePlayerController.h"

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// MouseX, Y 입력 시 호출할 메서드를 바인딩시킵니다.
	InputComponent->BindAxis(TEXT("MouseX"), this, &AGamePlayerController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &AGamePlayerController::MouseYInput);
}

void AGamePlayerController::MouseXInput(float axis)
{
	// 컨트롤러의 Yaw 회전값에 axis 를 더합니다.
	/// - axis : 마우스를 왼쪽으로 이동시킨다면 -1
	/// -        마우스를 오른쪽으로 이동시킨다면 1
	AddYawInput(axis);
}

void AGamePlayerController::MouseYInput(float axis)
{
	// 컨트롤러의 Pitch 회전값에 axis 를 더합니다.
	/// - axis : 마우스를 위쪽으로 이동시킨다면 -1
	/// -        마우스를 아래쪽으로 이동시킨다면 1
	AddPitchInput(axis);
}
