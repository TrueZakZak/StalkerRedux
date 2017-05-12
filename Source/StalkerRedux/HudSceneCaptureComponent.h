// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneCaptureComponent2D.h"
#include "HudSceneCaptureComponent.generated.h"

/**
 * 
 */
UCLASS()
class STALKERREDUX_API UHudSceneCaptureComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()
	
public:
	void SetFieldOfView(float FieldOfView);
};
