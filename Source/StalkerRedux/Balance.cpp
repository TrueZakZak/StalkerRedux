// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "Balance.h"

UBalance::UBalance(const FObjectInitializer& Initializer)
	: Super(Initializer)
{

}

UBalanceLibrary* UBalance::Inst(bool &bIsValid)
{
	bIsValid = false;

	if (!GEngine)
	{
		return nullptr;
	}

	UBalanceLibrary* Data = Cast<UBalanceLibrary>(GEngine->GameSingleton);

	if (!Data)
	{
		return nullptr;
	}

	if (!Data->IsValidLowLevel())
	{
		return nullptr;
	}

	bIsValid = true;

	return Data;
}
