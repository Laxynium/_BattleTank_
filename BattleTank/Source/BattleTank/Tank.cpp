// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAmingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("I am firing"));
	if (!Barrel)return;
	auto Location = Barrel->GetSocketLocation("Projectile");
	auto Rotation = Barrel->GetSocketRotation("Projectile");
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, FRotator());
	Projectile->LaunchProjectitle(LaunchSpeed);
}
void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAmingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAmingComponent->SetTurretReference(TurretToSet);
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAmingComponent = CreateDefaultSubobject<UTankAmingComponent>(FName("Aming Component"));
	//SetBarrelReference
}


void ATank::AimAt(FVector HitLocation)
{
	TankAmingComponent->AimAt(HitLocation, LaunchSpeed);
	//Spawn a projectile at socket location on the barrel
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

