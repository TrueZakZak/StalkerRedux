// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "StalkerCharacterController.generated.h"

UCLASS()
class STALKERREDUX_API AStalkerCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStalkerCharacterController();

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveStrafe(float Value);

	UFUNCTION()
	void JumpStart();

	UFUNCTION()
	void JumpEnd();

protected:
	virtual void PostInitializeComponents() override;
	        void FirstTickInit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FpsCameraComponent;

	UPROPERTY(VisibleAnywhere)
	USceneCaptureComponent2D* SceneCapture2D;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* HandsMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool bFirstTickInitDone;
};
