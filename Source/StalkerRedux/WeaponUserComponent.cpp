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
		WeaponInfo->UnloadAssets();
		WeaponInfo = nullptr;
	}
}

// Called every frame
void UWeaponUserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
