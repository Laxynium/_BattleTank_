// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAmingComponent.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (countOfAmmo <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel&&Turret)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation= Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0
		,ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		moveBarrelToward(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus!=EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		if (!ensure(Barrel) || !ensure(ProjectileBlueprint))return;
		auto Location = Barrel->GetSocketLocation("Projectile");
		auto Rotation = Barrel->GetSocketRotation("Projectile");
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		Projectile->LaunchProjectitle(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		--countOfAmmo;
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetCountOfAmmo() const
{
	return countOfAmmo;
}

void UTankAimingComponent::moveBarrelToward(FVector AimDirection)
{
	if (!ensure(Barrel&&Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = (AimAsRotator - BarrelRotator);
	Barrel->Elevate(DeltaRotator.Pitch);
	//Always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else //Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))return false;
	auto BarrelForward=Barrel->GetForwardVector();
	if (!BarrelForward.Equals(AimDirection,0.01))
	{return true;}
	return false;
}
