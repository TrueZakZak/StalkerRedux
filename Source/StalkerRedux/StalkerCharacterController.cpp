// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "StalkerCharacterController.h"

#include "Balance.h"

// Sets default values
AStalkerCharacterController::AStalkerCharacterController()
	: bFirstTickInitDone(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FpsCamera"));
	FpsCameraComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	FpsCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f + BaseEyeHeight));
	FpsCameraComponent->bUsePawnControlRotation = true;

	SceneCapture2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Hands"));
	SceneCapture2D->AttachToComponent(FpsCameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SceneCapture2D->ShowFlags.SetFog(false);

	WeaponUser = CreateDefaultSubobject<UWeaponUserComponent>(TEXT("WeaponUser"));
	WeaponUser->AttachToComponent(FpsCameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AStalkerCharacterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SceneCapture2D->ShowOnlyActorComponents(this);
}

void AStalkerCharacterController::FirstTickInit()
{
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	SceneCapture2D->TextureTarget->InitAutoFormat((int32)ViewportSize.X, (int32)ViewportSize.Y);
	SceneCapture2D->TextureTarget->UpdateResourceImmediate();
}

// Called when the game starts or when spawned
void AStalkerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	bool Success;
	UBalanceLibrary* Balance = UBalance::Inst(Success);

	if (Success)
	{
		FWeaponInfo* WpnInfo = Balance->GetWeaponInfo(TEXT("wpn_vss"));
		WeaponUser->InitWeapon(WpnInfo);
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

	if (GEngine && !bFirstTickInitDone)
	{
		FirstTickInit();
		bFirstTickInitDone = true;
	}
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
