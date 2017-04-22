// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "BalanceLibrary.h"

UBalanceLibrary::UBalanceLibrary(const FObjectInitializer& Initializer)
	: UObject(Initializer)
{
}

FWeaponInfo* UBalanceLibrary::GetWeaponInfoByUID(const FString& WpnID)
{
	// Will be gread to do it on iniialization
	TryLoadAssets();

	UWeaponsDatabase* DB = Weapons.Get();
	return DB->GetByUID(WpnID);
}

FWeaponInfo* UBalanceLibrary::GetWeaponInfoByType(EWeaponType Type)
{
	// Will be gread to do it on iniialization
	TryLoadAssets();

	UWeaponsDatabase* DB = Weapons.Get();
	return DB->GetByType(Type);
}

void UBalanceLibrary::TryLoadAssets()
{
	if (Weapons.IsPending())
	{
		FStreamableManager Streamable;

		const FStringAssetReference& AssetRef = Weapons.ToStringReference();
		Weapons = Cast<UWeaponsDatabase>(Streamable.SynchronousLoad(AssetRef));
	}
}