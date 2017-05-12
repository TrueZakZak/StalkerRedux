// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponsDatabase.h"
#include "Components/ActorComponent.h"
#include "WeaponUserComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponShoot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKERREDUX_API UWeaponUserComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponUserComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitWeapon(FWeaponInfo* WpnInfo);

	void StartShooting();
	void StopShooting();

	void DoShoot();

	void StartAiming();
	void StopAiming();

	FWeaponInfo* GetWeaponInfo();

	FOnWeaponShoot OnShoot;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere) class USkeletalMeshComponent* HandsMesh;

	FWeaponInfo* WeaponInfo;

private:
	FRotator GetOrientationWithDispertionApplied(const FRotator& Original) const;
	FTransform GetProjectileStartingTransform(const FQuat& Orientation) const;
};
