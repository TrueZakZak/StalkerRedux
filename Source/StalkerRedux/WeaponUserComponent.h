// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponsDatabase.h"
#include "Components/ActorComponent.h"
#include "WeaponUserComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKERREDUX_API UWeaponUserComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponUserComponent();

	void InitWeapon(FWeaponInfo* WpnInfo);

	void StartShooting();
	void StopShooting();

	void DoShoot();

	void StartAiming();
	void StopAiming();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* HandsMesh;

	FWeaponInfo* WeaponInfo;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
