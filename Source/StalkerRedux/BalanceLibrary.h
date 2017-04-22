// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponsDatabase.h"

#include "UObject/NoExportTypes.h"
#include "BalanceLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class STALKERREDUX_API UBalanceLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	UBalanceLibrary(const FObjectInitializer& Initializer);

	FWeaponInfo* GetWeaponInfoByUID(const FString& WpnID);
	FWeaponInfo* GetWeaponInfoByType(EWeaponType Type);

private:
	UPROPERTY(EditAnywhere)
	TAssetPtr<UWeaponsDatabase> Weapons;

	void TryLoadAssets();
};
