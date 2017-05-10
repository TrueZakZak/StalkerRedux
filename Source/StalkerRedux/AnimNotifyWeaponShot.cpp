// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "AnimNotifyWeaponShot.h"

#include "WeaponUserComponent.h"

void UAnimNotifyWeaponShot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	auto *Owner = MeshComp->GetOwner();
	if (!Owner) return;

	auto *User = Owner->GetComponentByClass(UWeaponUserComponent::StaticClass());
	if (!User) return;

	auto* WeaponUser = Cast<UWeaponUserComponent>(User);
	if (!WeaponUser) return;

	ensureMsgf(WeaponUser != nullptr, TEXT("WeaponUser component is required for shooting"));

	WeaponUser->DoShoot();
}