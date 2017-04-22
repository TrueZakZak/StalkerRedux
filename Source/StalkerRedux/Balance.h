// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BalanceLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Balance.generated.h"

/**
 * 
 */
UCLASS()
class STALKERREDUX_API UBalance : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UBalance(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintPure, Category = "Balance")
	static UBalanceLibrary* Inst(bool &bIsValid);
};
