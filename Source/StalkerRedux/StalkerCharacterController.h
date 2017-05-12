// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WeaponUserComponent.h"
#include "ValueRusher.h"

#include "StalkerCharacterController.generated.h"

UCLASS()
class STALKERREDUX_API AStalkerCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStalkerCharacterController();
	~AStalkerCharacterController();

	UFUNCTION() void MoveForward(float Value);
	UFUNCTION() void MoveStrafe(float Value);

	UFUNCTION() void ShootingStart();
	UFUNCTION() void ShootingStop();

	UFUNCTION() void AimStart();
	UFUNCTION() void AimStop();

	UFUNCTION() void JumpStart();
	UFUNCTION() void JumpEnd();

	UFUNCTION() void CrouchStart();
	UFUNCTION() void CrouchEnd();

protected:
	virtual void PostInitializeComponents() override;
	        void FirstTickInit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere) class UCameraComponent*          FpsCameraComponent;
	UPROPERTY(EditAnywhere) class UHudSceneCaptureComponent* SceneCapture2D;
	UPROPERTY(EditAnywhere) class UWeaponUserComponent*      WeaponUser;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() void HandleOnWeaponShoot();

private:
	bool bFirstTickInitDone;

	UValueRusher MainZoomRusher;
	UValueRusher WeaponZoomRusher;
};
