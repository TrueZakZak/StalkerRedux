// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjetileMovement"));
	ProjectileMovement->SetUpdatedComponent(Mesh);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

	InitialLifeSpan = 3.0f;
}

void AProjectile::FireInDirection(const FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::BeginDestroy()
{
	Super::BeginDestroy();

	//Mesh->OnComponentHit.Clear();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpuls, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		FVector Direction;
		float Length;
		ProjectileMovement->Velocity.ToDirectionAndLength(Direction, Length);

		Direction *= 100.0f;

		OtherComponent->AddImpulseAtLocation((Direction * 500.0f), Hit.ImpactPoint);
	}

	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 25, 24, FColor::Red, false, 10.0f);

	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
