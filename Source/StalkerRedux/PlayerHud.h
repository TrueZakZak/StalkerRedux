// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class STALKERREDUX_API APlayerHud : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CursorTexture;

private:
	void DrawCursor();
};
