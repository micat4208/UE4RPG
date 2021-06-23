// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "GamePlayerController.generated.h"

UCLASS()
class UE4RPG_API AGamePlayerController : 
	public ABasePlayerController
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UPlayerHUD> BP_PlayerHUD;

public :
	AGamePlayerController();

protected :
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* pawn) override;

private :
	void CreatePlayerHUD();

	void MouseXInput(float axis);
	void MouseYInput(float axis);

private :
	void OpenInventory();

};
