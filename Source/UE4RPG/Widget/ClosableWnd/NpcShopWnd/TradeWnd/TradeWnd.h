// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "TradeWnd.generated.h"

/**
 * 
 */
UCLASS()
class UE4RPG_API UTradeWnd : public UClosableWnd
{
	GENERATED_BODY()

protected :
	virtual void NativeConstruct() override;
	
};
