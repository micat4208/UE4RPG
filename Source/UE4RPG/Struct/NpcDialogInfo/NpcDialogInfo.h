#pragma once

#include "CoreMinimal.h"
#include "NpcDialogInfo.generated.h"


USTRUCT(BluePrintType)
struct UE4RPG_API FNpcDialogInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	TArray<FText> DialogText; 

public :
	// 대화 내용이 비어있는지 확인합니다.
	bool IsEmpty() const;

public :
	// 마지막 대화 인덱스를 반환합니다.
	FORCEINLINE int32 GetLastDialogIndex() const
	{ return DialogText.Num() - 1; }

};
