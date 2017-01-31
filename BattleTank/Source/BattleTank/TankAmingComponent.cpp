// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAmingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
// Sets default values for this component's properties
UTankAmingComponent::UTankAmingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAmingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
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
		rotateTurret(AimDirection);
		auto Time = this->GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
	}
	else
	{
		auto Time = this->GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution not not not not found"), Time);
	}
	//MoveBarrel
	//GetBarrelRotator
	//SetBarrel Rotator correctly with OutLaunchVelocity
}

void UTankAmingComponent::moveBarrelToward(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAmingComponent::rotateTurret(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
	Turret->rotate(DeltaRotator.Yaw);
}



void UTankAmingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (Barrel)return;
	Barrel = BarrelToSet;
}

void UTankAmingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (Turret)return;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAmingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAmingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

