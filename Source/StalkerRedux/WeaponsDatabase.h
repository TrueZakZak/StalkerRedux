// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StalkerWeapons.h"

#include "Engine/DataAsset.h"
#include "WeaponsDatabase.generated.h"

/**
 *
 */
USTRUCT()
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString ID;

	UPROPERTY(EditAnywhere)
	EWeaponType Type;

	UPROPERTY(EditAnywhere, Category = ObjectDefinition)
	TAssetPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = ObjectDefinition)
	TAssetPtr<UAnimBlueprint> AnimBlueprint;

	void LoadAssets();
	void UnloadAssets();
};

/**
 * 
 */
UCLASS()
class STALKERREDUX_API UWeaponsDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UWeaponsDatabase(const FObjectInitializer& Initializer);

	FWeaponInfo* GetByUID(const FString& ID);
	FWeaponInfo* GetByType(EWeaponType Type);

private:
	UPROPERTY(EditAnywhere)
	TArray<FWeaponInfo> Items;
};
