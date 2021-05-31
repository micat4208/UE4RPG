// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UE4RPG_API UBaseSlot : 
	public UUserWidget
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
	class UImage * Image_SlotBackground;

	UPROPERTY(meta = (BindWidget))
	class UImage * Image_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Count;

};
