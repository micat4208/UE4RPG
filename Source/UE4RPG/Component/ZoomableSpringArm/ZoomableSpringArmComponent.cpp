#include "ZoomableSpringArmComponent.h"


UZoomableSpringArmComponent::UZoomableSpringArmComponent()
{

	bUseZoom = true;
	ArmLengthMin = 100.0f;
	ArmLengthMax = 200.0f;
}

void UZoomableSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetArmLength = ArmLengthTarget = 
		ArmLengthMin + (ArmLengthMax - ArmLengthMin);
}

void UZoomableSpringArmComponent::TickComponent(
	float dt, 
	ELevelTick tickType, 
	FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(dt, tickType, thisTickFunction);

	SmoothZoomSpringArm(dt);
}

void UZoomableSpringArmComponent::SmoothZoomSpringArm(float dt)
{
	TargetArmLength = FMath::FInterpTo(
		TargetArmLength, ArmLengthTarget, dt, 5.0f);
}

void UZoomableSpringArmComponent::ZoomCamera(float axis)
{
	// 줌을 사용하지 않는다면 실행 X
	if (!bUseZoom) return;

	ArmLengthTarget = FMath::Clamp(
		ArmLengthTarget + (axis * -5.0f), 
		ArmLengthMin, 
		ArmLengthMax);
}
