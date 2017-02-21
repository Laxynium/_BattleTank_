// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAmingComponent.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		moveBarrelToward(AimDirection);
	}
}

void UTankAimingComponent::moveBarrelToward(FVector AimDirection)
{
	if (!ensure(Barrel&&Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = (AimAsRotator - BarrelRotator);
	Barrel->Elevate(DeltaRotator.Pitch);
	//Ifs are to solve the problem with rotation
	if (DeltaRotator.Yaw>=180)
	{
		Turret->Rotate(-1);
	}
	else if (DeltaRotator.Yaw <= -180)
	{
		Turret->Rotate(1);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}

}