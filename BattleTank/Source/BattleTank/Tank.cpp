// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAmingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("ATank %s Constructor LOG"),*GetName());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATank BeginPlay LOG"),*GetName());
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel&&isReloaded)
	{
		auto Location = Barrel->GetSocketLocation("Projectile");
		auto Rotation = Barrel->GetSocketRotation("Projectile");
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		Projectile->LaunchProjectitle(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	
}
void ATank::AimAt(FVector HitLocation)
{
	if (!TankAmingComponent)return;
	TankAmingComponent->AimAt(HitLocation, LaunchSpeed);
	//Spawn a projectile at socket location on the barrel
}
