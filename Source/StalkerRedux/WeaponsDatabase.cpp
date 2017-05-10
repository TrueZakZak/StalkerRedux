// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "WeaponsDatabase.h"

void FWeaponAudioSetup::Load()
{
	FStreamableManager Streamable;

	if (Fire.IsPending())
	{
		const FStringAssetReference& AssetRef = Fire.ToStringReference();
		Fire = Cast<USoundWave>(Streamable.SynchronousLoad(AssetRef));
	}
}

void FWeaponAudioSetup::Unload()
{
	// Not implemented yet
}

void FWeaponInfo::LoadAssets()
{
	FStreamableManager Streamable;

	if (Mesh.IsPending())
	{
		const FStringAssetReference& AssetRef = Mesh.ToStringReference();
		Mesh = Cast<USkeletalMesh>(Streamable.SynchronousLoad(AssetRef));
	}

	if (AnimBlueprint.IsPending())
	{
		const FStringAssetReference& AssetRef = AnimBlueprint.ToStringReference();
		AnimBlueprint = Cast<UAnimBlueprint>(Streamable.SynchronousLoad(AssetRef));
	}

	AudioSetup.Load();
}

void FWeaponInfo::UnloadAssets()
{
	FStreamableManager Streamable;

	AudioSetup.Unload();

	if (!Mesh.IsPending())
	{
		const FStringAssetReference& AssetRef = Mesh.ToStringReference();
		Streamable.Unload(AssetRef);
	}

	if (!AnimBlueprint)
	{
		const FStringAssetReference& AssetRef = AnimBlueprint.ToStringReference();
		Streamable.Unload(AssetRef);
	}
}

UWeaponsDatabase::UWeaponsDatabase(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
}

FWeaponInfo* UWeaponsDatabase::GetByUID(const FString& ID)
{
	for (int32 I = 0; I < Items.Num(); ++I)
	{
		if (Items[I].ID.Equals(ID))
		{
			return &Items[I];
		}
	}

	return nullptr;
}

FWeaponInfo* UWeaponsDatabase::GetByType(EWeaponType Type)
{
	for (int32 I = 0; I < Items.Num(); ++I)
	{
		if (Items[I].Type == Type)
		{
			return &Items[I];
		}
	}

	return nullptr;
}
