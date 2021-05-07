#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZoomableSpringArmComponent.generated.h"

UCLASS()
class UE4RPG_API UZoomableSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

private :
	bool bUseZoom;
	float ArmLengthTarget;
	float ArmLengthMin;
	float ArmLengthMax;

public :
	UZoomableSpringArmComponent();

protected :
	virtual void BeginPlay() override;

public :
	virtual void TickComponent(
		float dt, 
		ELevelTick tickType, 
		FActorComponentTickFunction* thisTickFunction) override;

private :
	// 줌이 부드럽게 이루어지도록 합니다.
	void SmoothZoomSpringArm(float dt);

public :
	// 카메라 줌을 수행합니다.
	void ZoomCamera(float axis);

	// 줌이 가능한 최소, 최대 거리를 설정합니다.
	FORCEINLINE void SetArmLengthMinMax(float min, float max)
	{
		ArmLengthMin = min;
		ArmLengthMax = max;
	}
};
