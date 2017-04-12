// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "StalkerReduxGameModeBase.h"

void AStalkerReduxGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, TEXT("Custom Game Mode"));
	}
}