#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enum/InputModeType.h"

#include "WidgetController.generated.h"

UCLASS()
class UE4RPG_API UWidgetController final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	class ABasePlayerController* PlayerController;

	// �Ҵ�Ǿ��ִ� Widget ��ü���� ��Ÿ���ϴ�.
	/// - â ��ü�� �߰����� �ʽ��ϴ�.
	TArray<UUserWidget*> AllocatedWidgets;


private :
	// â ��ü���� �ƴ� HUD �� �߰��� ĵ����
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WidgetParent;

	// â ��ü���� �߰��� ĵ����
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WndParent;

private :
	// �Է� ���, Ŀ�� ǥ�ø� �⺻ ������ �ʱ�ȭ�մϴ�.
	/// - ���� �����̳�, â�� �����Ѵٸ� �Է� ��尡 �ʱ�ȭ���� �ʽ��ϴ�.
	/// - bForceChange : ���� �����̳�, â�� ���� ���θ� �����ϰ� ������ �ʱ�ȭ��ų �������� ���� ���θ� �����մϴ�.
	void ResetInputMode(bool bForceChange = false);

public :
	// Widget Controller �� �ʱ�ȭ�մϴ�.
	void InitializeWidgetController(class ABasePlayerController* playerController);

	// ���� ������ �߰��մϴ�.
	/// - �߰��� ������ CanvasPanel_WidgetParent ĵ���� ������ �߰��Ǹ�,
	///   â �����麸�� ����, ��ȣ�ۿ� �켱������ �����ϴ�.
	/// - childWidgetInstance : �߰��� ���� ���� ��ü�� �����մϴ�.
	/// - bShowMouseCursor : â�� ��� �� Ŀ���� ǥ���� �������� ���� ���θ� �����մϴ�.
	/// - width : ��� ������ �ʺ� �����մϴ�.
	/// - height : ��� ������ ���̸� �����մϴ�.
	void AddChildWidget(class UUserWidget* childWidgetInstance, 
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// �߰���Ų ���� ������ �ݽ��ϴ�.
	/// - childWidgetInstance : ���� ���� ��ü�� �����մϴ�.
	void CloseChildWidget(class UUserWidget* childWidgetInstance);


	
};
