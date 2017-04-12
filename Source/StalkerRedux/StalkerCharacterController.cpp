// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "StalkerCharacterController.h"


// Sets default values
AStalkerCharacterController::AStalkerCharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FpsCamera"));
	FpsCameraComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	FpsCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f + BaseEyeHeight));
	FpsCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AStalkerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Red, TEXT("Custom Character"));
	}
}

void AStalkerCharacterController::MoveForward(float Value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, Value);
}

void AStalkerCharacterController::MoveStrafe(float Value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, Value);
}

void AStalkerCharacterController::JumpStart()
{
	bPressedJump = true;
}

void AStalkerCharacterController::JumpEnd()
{
	bPressedJump = false;
}

// Called every frame
void AStalkerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStalkerCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AStalkerCharacterController::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AStalkerCharacterController::JumpEnd);

	PlayerInputComponent->BindAxis("MoveForward", this, &AStalkerCharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveStrafe", this, &AStalkerCharacterController::MoveStrafe);

	PlayerInputComponent->BindAxis("Turn", this, &AStalkerCharacterController::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AStalkerCharacterController::AddControllerPitchInput);
}
