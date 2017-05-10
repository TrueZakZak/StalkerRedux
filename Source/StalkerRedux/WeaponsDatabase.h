// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StalkerWeapons.h"
#include "Projectile.h"

#include "Engine/DataAsset.h"
#include "WeaponsDatabase.generated.h"

/**
 *
 */
USTRUCT()
struct FShootingSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere) float DispertionRateMin;
	UPROPERTY(EditAnywhere) float DispertionRateMax;

	UPROPERTY(EditAnywhere) float FireRate;
};

USTRUCT()
struct FWeaponAudioSetup
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere) TAssetPtr<USoundWave> Fire;
	UPROPERTY(EditAnywhere) TAssetPtr<USoundWave> Misfire;
	UPROPERTY(EditAnywhere) TAssetPtr<USoundWave> Reload;
	UPROPERTY(EditAnywhere) TAssetPtr<USoundWave> Draw;

	void Load();
	void Unload();
};

/**
 *
 */
USTRUCT()
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere) FString           ID;
	UPROPERTY(EditAnywhere) EWeaponType       Type;
	UPROPERTY(EditAnywhere) FShootingSettings ShootingSettings;
	UPROPERTY(EditAnywhere) FWeaponAudioSetup AudioSetup;

	UPROPERTY(EditAnywhere, Category = Assets) TAssetPtr<USkeletalMesh>  Mesh;
	UPROPERTY(EditAnywhere, Category = Assets) TAssetPtr<UAnimBlueprint> AnimBlueprint;

	UPROPERTY(EditAnywhere) TSubclassOf<AProjectile> Projectile;

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
	UPROPERTY(EditAnywhere) TArray<FWeaponInfo> Items;
};
