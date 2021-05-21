#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public :
	// Widget Controller �� �ʱ�ȭ�մϴ�.
	void InitializeWidgetController(class ABasePlayerController* playerController);

	// ���� ������ �߰��մϴ�.
	/// - �߰��� ������ CanvasPanel_WidgetParent ĵ���� ������ �߰��Ǹ�,
	///   â �����麸�� ����, ��ȣ�ۿ� �켱������ �����ϴ�.
	/// - childWidgetInstance : �߰��� ���� ���� ��ü�� �����մϴ�.
	void AddChildWidget(class UUserWidget* childWidgetInstance);


	
};
