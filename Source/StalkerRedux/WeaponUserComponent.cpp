// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "WeaponUserComponent.h"

#include "Balance.h"
#include "BalanceLibrary.h"
#include "WeaponsDatabase.h"

// Sets default values for this component's properties
UWeaponUserComponent::UWeaponUserComponent()
	: WeaponInfo(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	HandsMesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	HandsMesh->bOwnerNoSee = true;
	HandsMesh->CastShadow = 0;
}

void UWeaponUserComponent::InitWeapon(FWeaponInfo* WpnInfo)
{
	WeaponInfo = WpnInfo;

	WeaponInfo->LoadAssets();

	HandsMesh->SetSkeletalMesh(WeaponInfo->Mesh.Get());
	HandsMesh->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
	HandsMesh->SetAnimInstanceClass(WeaponInfo->AnimBlueprint.Get()->GeneratedClass);
}

void UWeaponUserComponent::StartShooting()
{
	UAnimInstance* AnimInst = HandsMesh->GetAnimInstance();
	UBoolProperty* PropBool = FindField<UBoolProperty>(AnimInst->GetClass(), "IsShootingInput");

	if (PropBool != nullptr)
	{
		PropBool->SetPropertyValue_InContainer(AnimInst, true);
	}
}

void UWeaponUserComponent::StopShooting()
{
	UAnimInstance* AnimInst = HandsMesh->GetAnimInstance();
	UBoolProperty* PropBool = FindField<UBoolProperty>(AnimInst->GetClass(), "IsShootingInput");

	if (PropBool != nullptr)
	{
		PropBool->SetPropertyValue_InContainer(AnimInst, false);
	}
}

FWeaponInfo* UWeaponUserComponent::GetWeaponInfo()
{
	return WeaponInfo;
}

FRotator UWeaponUserComponent::GetOrientationWithDispertionApplied(const FRotator& Original) const
{
	float DispertionMin = WeaponInfo->ShootingSettings.DispertionRateMin;
	float DispertionMax = WeaponInfo->ShootingSettings.DispertionRateMax;

	float DispertionYaw = FMath::RandRange(DispertionMin, DispertionMax);
	float DispertionPitch = FMath::RandRange(DispertionMin, DispertionMax);

	FRotator Dir(Original);

	Dir.Yaw += DispertionYaw * (FMath::RandBool() ? 1.0f : -1.0f);
	Dir.Pitch += DispertionPitch * (FMath::RandBool() ? 1.0f : -1.0f);

	return Dir;
}

FTransform UWeaponUserComponent::GetProjectileStartingTransform(const FQuat& Orientation) const
{
	const USkeletalMeshSocket *MuzzleSocket = HandsMesh->GetSocketByName("muzzle_sfx");
	ensureMsgf(MuzzleSocket != nullptr, TEXT("Failed to find weapon muzzle socket"));

	FTransform MuzzleTransform = MuzzleSocket->GetSocketTransform(HandsMesh);
	FTransform ProjectileTransform = FTransform::Identity;
	
	ProjectileTransform.SetTranslation(MuzzleTransform.GetTranslation());
	ProjectileTransform.SetRotation(Orientation);

	return ProjectileTransform;
}

void UWeaponUserComponent::DoShoot()
{
	FVector EyesPos;
	FRotator EyesDir;
	GetOwner()->GetActorEyesViewPoint(EyesPos, EyesDir);

	FRotator ShotDir = GetOrientationWithDispertionApplied(EyesDir);
	FTransform Transform = GetProjectileStartingTransform(ShotDir.Quaternion());

	UWorld *World = GetWorld();

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = GetOwner();

	AProjectile *Projectile = World->SpawnActor<AProjectile>(WeaponInfo->Projectile, Transform, SpawnParam);
	Projectile->FireInDirection(ShotDir.Vector());

	OnShoot.Broadcast();
}

void UWeaponUserComponent::StartAiming()
{

}

void UWeaponUserComponent::StopAiming()
{

}

// Called when the game starts
void UWeaponUserComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponUserComponent::BeginDestroy()
{
	Super::BeginDestroy();

	if (WeaponInfo)
	{
		//WeaponInfo->UnloadAssets();
		//WeaponInfo = nullptr;
	}
}

// Called every frame
void UWeaponUserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
