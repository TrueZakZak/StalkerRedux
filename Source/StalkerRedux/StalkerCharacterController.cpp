// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "StalkerCharacterController.h"

#include "Balance.h"
#include "HudSceneCaptureComponent.h"

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

	SceneCapture2D = CreateDefaultSubobject<UHudSceneCaptureComponent>(TEXT("Hands"));
	SceneCapture2D->AttachToComponent(FpsCameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SceneCapture2D->ShowFlags.SetFog(false);

	WeaponUser = CreateDefaultSubobject<UWeaponUserComponent>(TEXT("WeaponUser"));
	WeaponUser->AttachToComponent(FpsCameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	WeaponUser->OnShoot.AddDynamic(this, &AStalkerCharacterController::HandleOnWeaponShoot);

	MainZoomRusher.Init(90.0f);
	WeaponZoomRusher.Init(50.0f);
}

AStalkerCharacterController::~AStalkerCharacterController()
{
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
		FWeaponInfo* WpnInfo = Balance->GetWeaponInfoByType(EWeaponType::WPN_VINTOREZ);
		WeaponUser->InitWeapon(WpnInfo);
	}
}

void AStalkerCharacterController::BeginDestroy()
{
	Super::BeginDestroy();
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

void AStalkerCharacterController::ShootingStart()
{
	WeaponUser->StartShooting();
}

void AStalkerCharacterController::ShootingStop()
{
	WeaponUser->StopShooting();
}

void AStalkerCharacterController::AimStart()
{
	MainZoomRusher.RushTo(60.0f);
	WeaponZoomRusher.RushTo(40.0f);
}

void AStalkerCharacterController::AimStop()
{
	MainZoomRusher.RushBack(90.0f);
	WeaponZoomRusher.RushBack(50.0f);
}

void AStalkerCharacterController::JumpStart()
{
	bPressedJump = true;
}

void AStalkerCharacterController::JumpEnd()
{
	bPressedJump = false;
}

void AStalkerCharacterController::CrouchStart()
{
	Crouch();
}

void AStalkerCharacterController::CrouchEnd()
{
	UnCrouch();
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

	MainZoomRusher.Update(DeltaTime);
	WeaponZoomRusher.Update(DeltaTime);

	FpsCameraComponent->SetFieldOfView(MainZoomRusher.GetCurrentValue());
	SceneCapture2D->SetFieldOfView(WeaponZoomRusher.GetCurrentValue());
}

// Called to bind functionality to input
void AStalkerCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AStalkerCharacterController::ShootingStart);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AStalkerCharacterController::ShootingStop);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AStalkerCharacterController::AimStart);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AStalkerCharacterController::AimStop);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AStalkerCharacterController::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AStalkerCharacterController::JumpEnd);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AStalkerCharacterController::CrouchStart);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AStalkerCharacterController::CrouchEnd);

	PlayerInputComponent->BindAxis("MoveForward", this, &AStalkerCharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveStrafe", this, &AStalkerCharacterController::MoveStrafe);

	PlayerInputComponent->BindAxis("Turn", this, &AStalkerCharacterController::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AStalkerCharacterController::AddControllerPitchInput);
}

void AStalkerCharacterController::HandleOnWeaponShoot()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(9923, 20.0f, FColor::Yellow, TEXT("Sound"));
	}

	auto* Info = WeaponUser->GetWeaponInfo();
	auto* Sound = Info->AudioSetup.Fire.Get();
	UGameplayStatics::PlaySound2D(this, Sound);
}
